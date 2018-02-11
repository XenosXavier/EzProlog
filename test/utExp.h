#ifndef UT_EXP_H
#define UT_EXP_H
#include "../inc/matchingExp.h"
#include "../inc/andExp.h"
#include "../inc/orExp.h"
#include "../inc/atom.h"

TEST(Exp, matchingExp)
{
    MatchingExp mexp(new Atom("tom"), new Atom("jerry"));
    ASSERT_FALSE(mexp.evaluate());
    MatchingExp mexp2(new Atom("tom"), new Atom("tom"));
    ASSERT_TRUE(mexp2.evaluate());
}

TEST(Exp, andExp)
{
    MatchingExp mexp(new Atom("tom"), new Atom("jerry"));
    MatchingExp mexp2(new Atom("tom"), new Atom("tom"));
    AndExp aexp(&mexp, &mexp2);
    ASSERT_FALSE(aexp.evaluate());
    AndExp aexp2(&mexp2, &mexp2);
    ASSERT_TRUE(aexp2.evaluate());
}

TEST(Exp, orExp)
{
    MatchingExp mexp(new Atom("tom"), new Atom("jerry"));
    MatchingExp mexp2(new Atom("tom"), new Atom("tom"));
    OrExp oexp(&mexp, &mexp2);
    ASSERT_TRUE(oexp.evaluate());
    OrExp oexp2(&mexp, &mexp);
    ASSERT_FALSE(oexp2.evaluate());
}

#endif