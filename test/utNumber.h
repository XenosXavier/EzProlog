#ifndef UT_NUMBER_H
#define UT_NUMBER_H
#include "../inc/number.h"

TEST(Number, symbol)
{
    Number n1(-0.1);
    ASSERT_EQ("-0.1", n1.symbol());
}

TEST(Number, value)
{
    Number n1(-0.1);
    ASSERT_EQ("-0.1", n1.value());
}

TEST(Number, matchSuccess)
{
    Number n1(-0.1);
    Number n2(-0.1);
    ASSERT_TRUE(n1.match(&n2));
}

TEST(Number, matchFail)
{
    Number n1(-0.1);
    Number n2(0.1);
    ASSERT_FALSE(n1.match(&n2));
}

TEST(Number, getStructure)
{
    Number n1(-0.1);
    ASSERT_EQ(nullptr, n1.getStructure());
}

TEST(Number, getVariable)
{
    Number n1(-0.1);
    ASSERT_EQ(nullptr, n1.getVariable());
}

#endif