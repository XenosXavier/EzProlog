#ifndef UT_NUMBER_H
#define UT_NUMBER_H
#include "../inc/number.h"

TEST(number, symbol)
{
    Number n1(-0.1);
    ASSERT_EQ("-0.1", n1.symbol());
}

TEST(number, value)
{
    Number n1(-0.1);
    ASSERT_EQ("-0.1", n1.value());
}

TEST(number, match)
{
    Number n1(-0.1);
    Number n2(0.1);
    Number n3(-0.1);
    ASSERT_FALSE(n1.match(&n2));
    ASSERT_TRUE(n1.match(&n3));
}

TEST(number, getStructure)
{
    Number n1(-0.1);
    ASSERT_FALSE(n1.getStructure());
}

TEST(number, getVariable)
{
    Number n1(-0.1);
    ASSERT_FALSE(n1.getVariable());
}

#endif