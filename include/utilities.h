#ifndef VC_UTILITIES
#define VC_UTILITIES

#include "vclock.h"

namespace vc
{
    /*
     * Determine if lhs and rhs do or do not violate causality
     * i.e. if ( lhs != rhs ) && !( lhs < rhs ) && !( rhs < lhs )
     * then lhs and rhs are not comparible
     */
    bool comparible(const vclock &lhs, const vclock &rhs);
}

#endif