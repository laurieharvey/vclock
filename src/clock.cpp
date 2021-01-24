#include <cassert>
#include <algorithm>

#include "clock.h"

namespace vc
{
    sclock::sclock(tick_type tick)
        : tick(tick)
    {
    }

    bool operator<(const sclock &lhs, const sclock &rhs)
    {
        return lhs.tick < rhs.tick;
    }

    bool operator>(const sclock &lhs, const sclock &rhs)
    {
        return lhs.tick > rhs.tick;
    }

    bool operator<=(const sclock &lhs, const sclock &rhs)
    {
        return lhs.tick <= rhs.tick;
    }

    bool operator>=(const sclock &lhs, const sclock &rhs)
    {
        return lhs.tick >= rhs.tick;
    }

    bool operator==(const sclock &lhs, const sclock &rhs)
    {
        return lhs.tick == rhs.tick;
    }

    void sclock::operator++(int)
    {
        tick++;
    }
} // namespace vc