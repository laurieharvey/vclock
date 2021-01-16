#include <vector>
#include <string>

namespace vc
{
    struct clock
    {
        using name_type = std::string;
        using tick_type = long long int;

        name_type name;
        tick_type tick;

        void operator++();

        void update(const clock &other);

        friend bool operator<(const clock &lhs, const clock &rhs);
        friend bool operator>(const clock &lhs, const clock &rhs);

        friend bool operator<=(const clock &lhs, const clock &rhs);
        friend bool operator>=(const clock &lhs, const clock &rhs);
        friend bool operator==(const clock &lhs, const clock &rhs);
    };

    class vclock
    {
        std::vector<clock> causal_history;
    public:
        using name_type = clock::name_type;
        using tick_type = clock::tick_type;

        clock default_clock;
        clock last_ticked;

        explicit vclock(clock default_clock);

        void tick();

        void merge(const vclock &other);

        bool operator<(const vclock &rhs) const;

        bool operator==(const vclock &rhs) const;

        bool operator>(const vclock &rhs) const;
    };
} // namespace vc