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

        explicit vclock(clock_type default_clock);

        void tick();

        friend void merge(const vclock &src, vclock &dest);

        friend bool operator<(const vclock &lhs, const vclock &rhs);
        friend bool operator>(const vclock &lhs, const vclock &rhs);

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