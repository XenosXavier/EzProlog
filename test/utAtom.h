#ifndef UT_ATOM_H
#define UT_ATOM_H
#include "../inc/atom.h"

TEST(atom, symbol)
{
    Atom tom("tom");
    ASSERT_EQ("tom", tom.symbol());
}

TEST(atom, value)
{
    Atom tom("tom");
    ASSERT_EQ("tom", tom.symbol());
}

TEST(atom, match)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom anotherTom("tom");
    ASSERT_FALSE(tom.match(&jerry));
    ASSERT_TRUE(tom.match(&anotherTom));
}

TEST(atom, getStructure)
{
    Atom tom("tom");
    ASSERT_FALSE(tom.getStructure());
}

TEST(atom, getVariable)
{
    Atom tom("tom");
    ASSERT_FALSE(tom.getVariable());
}

#endif