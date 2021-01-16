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