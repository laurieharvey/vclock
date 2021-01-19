#ifndef VC_CLOCK
#define VC_CLOCK

#include <string>

namespace vc
{
    struct clock
    {
        using name_type = std::string;
        using tick_type = long long int;

        name_type name;
        tick_type tick;

        /*
         * Construct the scalar clock with name and starting time
         */
        explicit clock(name_type name, tick_type tick);

        /*
         * Increment the scalar clock's hand
         */
        void operator++(int);

        /*
         * Binary relations for the totally ordered set
         */
        friend bool operator< (const clock &lhs, const clock &rhs);
        friend bool operator> (const clock &lhs, const clock &rhs);
        friend bool operator<=(const clock &lhs, const clock &rhs);
        friend bool operator>=(const clock &lhs, const clock &rhs);
        friend bool operator==(const clock &lhs, const clock &rhs);
    };
} // namespace vc

#endif