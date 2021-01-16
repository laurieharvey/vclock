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

    vclock::vclock(clock default_clock)
        : causal_history({default_clock}), default_clock(default_clock), last_ticked(default_clock)
    {
    }

    void vclock::tick()
    {
        ++(*std::find(std::begin(causal_history), std::end(causal_history), default_clock));
    }

    void vclock::merge(const vclock &other)
    {
        bool precedes = true;

        for (const auto &c : other.causal_history)
        {
            auto this_clock = std::find(std::begin(causal_history), std::end(causal_history), default_clock);

            if (this_clock == std::cend(causal_history))
            {
                causal_history.push_back(*this_clock);
                precedes = false;
            }
            else
            {
                if ((*this_clock) < c)
                {
                    this_clock->update(c);
                }
                else if ((*this_clock) > c)
                {
                    precedes = false;
                }
            }
        }

        if (precedes)
        {
            last_ticked = other.last_ticked;
        }
        else
        {
            tick();
        }
    }

    bool vclock::operator<(const vclock &rhs) const
    {
        auto rhs_clock = std::find_if(std::begin(rhs.causal_history), std::end(rhs.causal_history), 
           [this](const clock& c){ return this->last_ticked.name == c.name; });

        if (rhs_clock == std::cend(rhs.causal_history))
        {
            return false;
        }
        else
        {
            return last_ticked < *rhs_clock;
        }
    }

    bool vclock::operator==(const vclock &rhs) const
    {
        return last_ticked.name == rhs.last_ticked.name && last_ticked == rhs.last_ticked;
    }

    bool vclock::operator>(const vclock &rhs) const
    {
        auto rhs_clock = std::find_if(std::begin(rhs.causal_history), std::end(rhs.causal_history), 
           [this](const clock& c){ return this->last_ticked.name == c.name; });
           
        if (rhs_clock == std::cend(rhs.causal_history))
        {
            return false;
        }
        else
        {
            return last_ticked > *rhs_clock;
        }
    }
} // namespace vc