#ifndef UT_VARIABLE_H
#define UT_VARIABLE_H
#include "../inc/variable.h"
#include "../inc/structure.h"
#include "../inc/number.h"

TEST(variable, symbol)
{
    Variable X("X");
    ASSERT_EQ("X", X.symbol());
}

TEST(variable, value)
{
    Variable X("X");
    ASSERT_EQ("X", X.value());
    Atom tom("tom");
    X.match(&tom);
    ASSERT_EQ("tom", X.value());
}

TEST(variable, matchAtom)
{
    Variable X("X");
    Atom tom("tom");
    Atom jerry("jerry");
    ASSERT_TRUE(X.match(&tom));
    ASSERT_FALSE(X.match(&jerry));
}

TEST(variable, matchNumber)
{
    Variable X("X");
    Number n1(-0.1);
    Number n2(0.1);
    ASSERT_TRUE(X.match(&n1));
    ASSERT_FALSE(X.match(&n2));
}

TEST(variable, matchStructure)
{
    Variable X("X");
    Structure s1(new Atom("s1"), {});
    Structure s2(new Atom("s2"), {});
    ASSERT_TRUE(X.match(&s1));
    ASSERT_FALSE(X.match(&s2));
}

TEST(variable, getStructure)
{
    Variable X("X");
    ASSERT_FALSE(X.getStructure());
}

TEST(variable, getVariable)
{
    Variable X("X");
    ASSERT_TRUE(X.getVariable());
    ASSERT_EQ(&X, X.getVariable());
}

#endif