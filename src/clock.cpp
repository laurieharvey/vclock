#include <cassert>
#include <algorithm>

#include "clock.h"

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
} // namespace vc