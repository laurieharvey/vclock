#include <cassert>
#include <algorithm>

#include "vclock.h"
#include "clock.h"

namespace vc
{
    struct same_clock
    {
        clock::name_type lhs;

        bool operator()(const clock &rhs) const
        {
            return rhs.name == lhs;
        }
    };

    vclock::vclock(clock default_clock)
        : causal_history({default_clock}), default_clock(default_clock.name), last_ticked(default_clock.name)
    {
    }

    void vclock::tick()
    {
        ++(*std::find_if(std::begin(causal_history), std::end(causal_history), same_clock{default_clock}));
        last_ticked = default_clock;
    }

    void merge(const vclock &src, vclock &dest)
    {
        bool src_has_dst_clocks = true, no_dst_clocks_supercede_src = true, one_dst_clock_precedes_src = false;

        for (const auto &src_clock : src.causal_history)
        {
            auto dst_clock = std::find_if(std::begin(dest.causal_history), std::end(dest.causal_history), same_clock{src_clock.name});

            if (dst_clock == std::cend(dest.causal_history))
            {
                one_dst_clock_precedes_src = true;

                dest.causal_history.push_back(src_clock);
            }
            else
            {
                if ((*dst_clock) < src_clock)
                {
                    one_dst_clock_precedes_src = true;

                    dst_clock->update(src_clock);
                }
                else if ((*dst_clock) > src_clock)
                {
                    no_dst_clocks_supercede_src = false;
                }
            }
        }

        if (dest.causal_history.size() != src.causal_history.size())
            src_has_dst_clocks = false;

        bool dst_precedes_src = src_has_dst_clocks && no_dst_clocks_supercede_src && one_dst_clock_precedes_src;

        if (dst_precedes_src)
        {
            dest.last_ticked = src.last_ticked;
        }
        else
        {
            dest.tick();
        }
    }

    bool operator<(const vclock &lhs, const vclock &rhs)
    {
        auto rhs_clock = std::find_if(std::begin(rhs.causal_history), std::end(rhs.causal_history), same_clock{lhs.last_ticked});

        auto lhs_last_ticked = std::find_if(std::cbegin(lhs.causal_history), std::cend(lhs.causal_history), same_clock{lhs.last_ticked});

        if (rhs_clock == std::cend(rhs.causal_history))
        {
            return false;
        }
        else
        {
            return *lhs_last_ticked < *rhs_clock || *lhs_last_ticked == *rhs_clock && lhs.last_ticked != rhs.last_ticked;
        }
    }

    bool operator>(const vclock &lhs, const vclock &rhs)
    {
        auto lhs_clock = std::find_if(std::begin(lhs.causal_history), std::end(lhs.causal_history), same_clock{rhs.last_ticked});

        auto rhs_last_ticked = std::find_if(std::cbegin(rhs.causal_history), std::cend(rhs.causal_history), same_clock{rhs.last_ticked});

        if (lhs_clock == std::cend(lhs.causal_history))
        {
            return false;
        }
        else
        {
            return *rhs_last_ticked < *lhs_clock || *rhs_last_ticked == *lhs_clock && lhs.last_ticked != rhs.last_ticked;
        }
    }

    bool operator<=(const vclock &lhs, const vclock &rhs)
    {
        return lhs < rhs || lhs == rhs;
    }

    bool operator>=(const vclock &lhs, const vclock &rhs)
    {
        return lhs > rhs || lhs == rhs;
    }

    bool operator==(const vclock &lhs, const vclock &rhs)
    {
        auto lhs_last_ticked = std::find_if(std::cbegin(lhs.causal_history), std::cend(lhs.causal_history), same_clock{lhs.last_ticked});
        auto rhs_last_ticked = std::find_if(std::cbegin(rhs.causal_history), std::cend(rhs.causal_history), same_clock{rhs.last_ticked});

        return lhs.last_ticked == rhs.last_ticked && *lhs_last_ticked == *rhs_last_ticked;
    }
} // namespace vc