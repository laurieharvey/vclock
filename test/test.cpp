#include "gtest/gtest.h"

#include "vclock.h"
#include "utilities.h"

TEST(poset, reflexivity)
{
    EXPECT_LE(vc::vclock("a",vc::clock(0)), vc::vclock("a",vc::clock(1)));
}

TEST(poset, antisymmetry)
{
    vc::vclock a("a",vc::clock(0));
    vc::vclock b("b",vc::clock(0));

    merge(a, b);

    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(a >= b);
}

TEST(poset, transitivity)
{
    vc::vclock a("a",vc::clock(0));
    vc::vclock b("b",vc::clock(0));
    vc::vclock c("c",vc::clock(0));

    merge(a, b);
    merge(b, c);

    EXPECT_LE(a, b);
    EXPECT_LE(b, c);
    EXPECT_LE(a, c);
}

TEST(vclock, precedes)
{
    EXPECT_LT(vc::vclock("a",vc::clock(0)), vc::vclock("a",vc::clock(1)));
}

TEST(vclock, supersedes)
{
    EXPECT_GT(vc::vclock("a",vc::clock(1)), vc::vclock("a",vc::clock(0)));
}

TEST(vclock, equals)
{
    EXPECT_EQ(vc::vclock("a",vc::clock(0)), vc::vclock("a",vc::clock(0)));
}

TEST(vclock, merge)
{
    vc::vclock a("a",vc::clock(0));
    vc::vclock b("b",vc::clock(0));

    merge(b, a);

    EXPECT_LT(b, a);
    EXPECT_GT(a, b);

    merge(a, b);

    EXPECT_EQ(a, b);
    EXPECT_EQ(b, a);
}

TEST(vclock, comparible)
{
    vc::vclock a("a",vc::clock(0));
    vc::vclock b("b",vc::clock(0));

    EXPECT_FALSE(vc::comparible(a, b));
    EXPECT_FALSE(vc::comparible(b, a));

    merge(b, a);

    EXPECT_TRUE(vc::comparible(a, b));
    EXPECT_TRUE(vc::comparible(b, a));

    merge(a, b);

    EXPECT_TRUE(vc::comparible(a, b));
    EXPECT_TRUE(vc::comparible(b, a));
}

TEST(vclock, full)
{
    vc::vclock a("a",vc::clock(0));
    vc::vclock b("b",vc::clock(0));
    vc::vclock c("c",vc::clock(0));

    EXPECT_FALSE(vc::comparible(a, b));
    EXPECT_FALSE(vc::comparible(b, c));
    EXPECT_FALSE(vc::comparible(c, a));

    merge(a, b);

    EXPECT_TRUE(vc::comparible(a, b));
    EXPECT_FALSE(vc::comparible(b, c));
    EXPECT_FALSE(vc::comparible(c, a));

    EXPECT_LT(a, b);
    EXPECT_GT(b, a);
    
    b++;

    EXPECT_TRUE(vc::comparible(a, b));
    EXPECT_FALSE(vc::comparible(b, c));
    EXPECT_FALSE(vc::comparible(c, a));

    EXPECT_LT(a, b);
    EXPECT_GT(b, a);

    merge(b, c);

    EXPECT_TRUE(vc::comparible(a, b));
    EXPECT_TRUE(vc::comparible(b, c));
    EXPECT_TRUE(vc::comparible(c, a));

    EXPECT_LT(a, b);
    EXPECT_LT(b, c);
    EXPECT_LT(a, c);
    EXPECT_GT(c, b);
    EXPECT_GT(b, a);
    EXPECT_GT(c, a);

    merge(c, a);

    EXPECT_EQ(c, a);
    EXPECT_EQ(a, c);
    EXPECT_GT(a, b);
    EXPECT_LT(b, a);
    
    a++;
    b++;
    c++;

    EXPECT_FALSE(vc::comparible(a, b));
    EXPECT_FALSE(vc::comparible(b, c));
    EXPECT_FALSE(vc::comparible(c, a));
}