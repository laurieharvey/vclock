#include <cassert>
#include <algorithm>

#include "vclock.h"

namespace vc
{
    bool operator<(const clock &lhs, const clock &rhs)
    {
        assert(lhs.name == rhs.name);

        return lhs.tick < rhs.tick;
    }

    bool operator>(const clock &lhs, const clock &rhs)
    {
        assert(lhs.name == rhs.name);

        return lhs.tick > rhs.tick;
    }

    bool operator<=(const clock &lhs, const clock &rhs)
    {
        assert(lhs.name == rhs.name);

        return lhs.tick <= rhs.tick;
    }

    bool operator>=(const clock &lhs, const clock &rhs)
    {
        assert(lhs.name == rhs.name);

        return lhs.tick >= rhs.tick;
    }

    bool operator==(const clock &lhs, const clock &rhs)
    {
        assert(lhs.name == rhs.name);

        return lhs.tick == rhs.tick;
    }

    void clock::operator++()
    {
        tick++;
    }

    void clock::update(const clock &other)
    {
        assert(name == other.name);

        tick = std::max(tick, other.tick);
    }

    struct same_clock
    {
        clock lhs;

        bool operator()(const clock &rhs) const
        {
            return rhs.name == lhs.name;
        }
    };

    vclock::vclock(clock default_clock)
        : causal_history({default_clock}), default_clock(default_clock), last_ticked(default_clock)
    {
    }

    void vclock::tick()
    {
        ++(*std::find_if(std::begin(causal_history), std::end(causal_history), same_clock{default_clock}));
        last_ticked = default_clock;
    }

    void vclock::merge(const vclock &src)
    {
        bool src_has_dst_clocks = true, no_dst_clocks_supercede_src = true, one_dst_clock_precedes_src = false;

        for (const auto &src_clock : src.causal_history)
        {
            auto dst_clock = std::find_if(std::begin(causal_history), std::end(causal_history), same_clock{src_clock});

            if (dst_clock == std::cend(causal_history))
            {
                one_dst_clock_precedes_src = true;

                causal_history.push_back(src_clock);
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

        if (causal_history.size() != src.causal_history.size())
            src_has_dst_clocks = false;

        bool dst_precedes_src = src_has_dst_clocks && no_dst_clocks_supercede_src && one_dst_clock_precedes_src;

        if (dst_precedes_src)
        {
            last_ticked = src.last_ticked;
        }
        else
        {
            tick();
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
            return *lhs_last_ticked < *rhs_clock || *lhs_last_ticked == *rhs_clock && lhs.last_ticked.name != rhs.last_ticked.name;
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
            return *rhs_last_ticked < *lhs_clock || *rhs_last_ticked == *lhs_clock && lhs.last_ticked.name != rhs.last_ticked.name;
        }
    }

    bool operator==(const vclock &lhs, const vclock &rhs)
    {
        return lhs.last_ticked.name == rhs.last_ticked.name && lhs.last_ticked == rhs.last_ticked;
    }
} // namespace vc