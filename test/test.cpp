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

    a.merge(b);

    EXPECT_GT(a, b);
}