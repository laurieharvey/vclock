#include <cassert>
#include <algorithm>

#include "clock.h"

namespace vc
{
    clock::clock(tick_type tick)
        : tick(tick)
    {
    }

    bool operator<(const clock &lhs, const clock &rhs)
    {
        return lhs.tick < rhs.tick;
    }

    bool operator>(const clock &lhs, const clock &rhs)
    {
        return lhs.tick > rhs.tick;
    }

    bool operator<=(const clock &lhs, const clock &rhs)
    {
        return lhs.tick <= rhs.tick;
    }

    bool operator>=(const clock &lhs, const clock &rhs)
    {
        return lhs.tick >= rhs.tick;
    }

    bool operator==(const clock &lhs, const clock &rhs)
    {
        return lhs.tick == rhs.tick;
    }

    void clock::operator++(int)
    {
        tick++;
    }
} // namespace vc