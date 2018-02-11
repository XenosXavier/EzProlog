#ifndef UT_ATOM_H
#define UT_ATOM_H
#include "../inc/atom.h"

TEST(Atom, symbol)
{
    Atom atom("tom");
    ASSERT_EQ("tom", atom.symbol());
}

TEST(Atom, value)
{
    Atom atom("tom");
    ASSERT_EQ("tom", atom.value());
}

TEST(Atom, matchSuccess)
{
    Atom atom("tom");
    Atom other("tom");
    ASSERT_TRUE(atom.match(&other));
}

TEST(Atom, matchFail)
{
    Atom atom("tom");
    Atom other("jerry");
    ASSERT_FALSE(atom.match(&other));
}

TEST(Atom, getStructure)
{
    Atom atom("tom");
    ASSERT_EQ(nullptr, atom.getStructure());
}

TEST(Atom, getVariable)
{
    Atom atom("tom");
    ASSERT_EQ(nullptr, atom.getVariable());
}

#endif