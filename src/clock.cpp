#include <cassert>
#include <algorithm>

#include "clock.h"

namespace vc
{
    clock::clock(name_type name, tick_type tick)
        : name(name), tick(tick)
    {
    }

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

    void clock::operator++(int)
    {
        tick++;
    }
} // namespace vc