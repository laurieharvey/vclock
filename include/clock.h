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

        explicit clock(name_type name, tick_type tick);

        void operator++(int);

        void update(const clock &other);

        friend bool operator< (const clock &lhs, const clock &rhs);
        friend bool operator> (const clock &lhs, const clock &rhs);
        friend bool operator<=(const clock &lhs, const clock &rhs);
        friend bool operator>=(const clock &lhs, const clock &rhs);
        friend bool operator==(const clock &lhs, const clock &rhs);
    };
} // namespace vc

#endif