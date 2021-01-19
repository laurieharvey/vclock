#ifndef VC_VCLOCK
#define VC_VCLOCK

#include <vector>
#include <string>

#include "clock.h"

namespace vc
{
    class vclock
    {
    public:
        using clock_type = clock;

        /*
         * Constuct the vector clock with the local scalar clock
         */
        explicit vclock(clock_type local_clock);

        /*
         * Merge two vector clocks
         * If dest precedes src then update dest (dest after == src)
         * If dest and src are not comparible then merge into dest
         * and increment the result (dest before < dest after)
         */
        friend void merge(const vclock &src, vclock &dest);

        /*
         * Increment the vector clock's hand
         */
        void operator++(int);

        /*
         * Binary relations for the partially ordered set
         */
        friend bool operator< (const vclock &lhs, const vclock &rhs);
        friend bool operator> (const vclock &lhs, const vclock &rhs);
        friend bool operator<=(const vclock &lhs, const vclock &rhs);
        friend bool operator>=(const vclock &lhs, const vclock &rhs);
        friend bool operator==(const vclock &lhs, const vclock &rhs);

    private:
        std::vector<clock_type> causal_history;
        clock_type::name_type default_clock;
        clock_type::name_type last_ticked;
    };
} // namespace vc

#endif
