#ifndef VC_CLOCK
#define VC_CLOCK

#include <string>

namespace vc
{
    class clock
    {
    public:
        using name_type = std::string;
        using tick_type = long long int;

        /*
         * Construct the scalar clock with name and starting time
         */
        explicit clock(tick_type tick);

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

    private:
        tick_type tick;
    };
} // namespace vc

#endif