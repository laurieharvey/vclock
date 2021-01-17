#include "gtest/gtest.h"

#include "vclock.h"

TEST(vclock, precedes)
{
    EXPECT_LT(vc::vclock(vc::clock{"a", 0}), vc::vclock(vc::clock{"a", 1}));
}

TEST(vclock, supersedes)
{
    EXPECT_GT(vc::vclock(vc::clock{"a", 1}), vc::vclock(vc::clock{"a", 0}));
}

TEST(vclock, equals)
{
    EXPECT_EQ(vc::vclock(vc::clock{"a", 0}), vc::vclock(vc::clock{"a", 0}));
}

TEST(vclock, merge)
{
    vc::vclock a(vc::clock{"a", 0});
    vc::vclock b(vc::clock{"b", 0});

    merge(b, a);

    EXPECT_LT(b, a);
    EXPECT_GT(a, b);

    merge(a, b);

    EXPECT_EQ(a, b);
    EXPECT_EQ(b, a);
}