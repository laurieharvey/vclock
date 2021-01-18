#include "utilities.h"

namespace vc
{
    bool comparible(const vclock &lhs, const vclock &rhs)
    {
        return lhs < rhs || rhs < lhs || lhs == rhs;
    }
} // namespace vc