#include <cassert>
#include <algorithm>

#include "vclock.h"
#include "clock.h"

namespace vc
{
    vclock::vclock(clock_type::name_type local_clock_name, clock local_clock)
        : causal_history{{local_clock_name, local_clock}}
        , local_clock_(local_clock_name)
        , last_ticked_(local_clock_name)
    {
    }

    void merge(const vclock &src, vclock &dest)
    {
        bool src_has_dst_clocks = true, no_dest_clocks_supercede_src = true, one_dest_clock_precedes_src = false;

        for (const auto &src_name_clock : src.causal_history)
        {
            const auto& src_clock_name = src_name_clock.first;
            const auto& src_clock = src_name_clock.second;

            auto dest_name_clock_iter = dest.causal_history.find(src_clock_name);

            if (dest_name_clock_iter == std::cend(dest.causal_history))
            {
                one_dest_clock_precedes_src = true;
                dest.causal_history.insert(src_name_clock);
            }
            else
            {
                auto& dest_clock_name = dest_name_clock_iter->first;
                auto& dest_clock = dest_name_clock_iter->second;

                if (dest_clock < src_clock)
                {
                    one_dest_clock_precedes_src = true;
                    dest_clock = src_clock;
                }
                else if (dest_clock > src_clock)
                {
                    no_dest_clocks_supercede_src = false;
                }
            }
        }

        if (dest.causal_history.size() != src.causal_history.size())
        {
            src_has_dst_clocks = false;
        }

        bool dest_precedes_src = src_has_dst_clocks && no_dest_clocks_supercede_src && one_dest_clock_precedes_src;

        if (dest_precedes_src)
        {
            dest.last_ticked_ = src.last_ticked_;
        }
        else
        {
            dest++;
        }
    }

    void vclock::operator++(int)
    {
        causal_history.find(local_clock_)->second++;
        last_ticked_ = local_clock_;
    }

    bool operator<(const vclock &lhs, const vclock &rhs)
    {
        const auto& rhs_name_clock_iter = rhs.causal_history.find(lhs.last_ticked_);

        if (rhs_name_clock_iter == std::cend(rhs.causal_history))
        {
            return false;
        }
        else
        {
            const auto& rhs_clock = rhs_name_clock_iter->second;
            const auto& lhs_clock = lhs.causal_history.find(lhs.last_ticked_)->second;

            return lhs_clock < rhs_clock || lhs_clock == rhs_clock && lhs.last_ticked_ != rhs.last_ticked_;
        }
    }

    bool operator>(const vclock &lhs, const vclock &rhs)
    {
        const auto& lhs_name_clock_iter = lhs.causal_history.find(rhs.last_ticked_);

        if (lhs_name_clock_iter == std::cend(lhs.causal_history))
        {
            return false;
        }
        else
        {
            const auto& lhs_clock = lhs_name_clock_iter->second;
            const auto& rhs_clock = rhs.causal_history.find(rhs.last_ticked_)->second;

            return rhs_clock < lhs_clock || rhs_clock == lhs_clock && lhs.last_ticked_ != rhs.last_ticked_;
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
        auto lhs_last_ticked = lhs.causal_history.find(lhs.last_ticked_)->second;
        auto rhs_last_ticked = rhs.causal_history.find(rhs.last_ticked_)->second;

        return lhs.last_ticked_ == rhs.last_ticked_ && lhs_last_ticked == rhs_last_ticked;
    }
} // namespace vc