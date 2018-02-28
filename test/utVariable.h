#ifndef UT_VARIABLE_H
#define UT_VARIABLE_H
#include "../inc/number.h"
#include "../inc/variable.h"
#include "../inc/structure.h"

TEST(Variable, symbol)
{
    Variable X("X", 0);
    ASSERT_EQ("X", X.symbol());
}

TEST(Variable, valueBeforeInstantiating)
{
    Variable X("X", 0);
    ASSERT_EQ("X", X.value());
}

TEST(Variable, instantiateAtom)
{
    Variable X("X", 0);
    Atom atom("tom");
    X.match(&atom);
    ASSERT_EQ("tom", X.value());
}

TEST(Variable, instantiateNumber)
{
    Variable X("X", 0);
    Number n1(-0.1);
    X.match(&n1);
    ASSERT_EQ("-0.1", X.value());
}

TEST(Variable, instantiateStructure)
{
    Variable X("X", 0);
    Structure s(new Atom("s"), {});
    X.match(&s);
    ASSERT_EQ("s()", X.value());
}

TEST(Variable, matchWithoutInstance)
{
    Variable X("X", 0);
    Atom atom("tom");
    ASSERT_TRUE(X.match(&atom));
    Variable Y("Y", 1);
    Number number(-0.1);
    ASSERT_TRUE(Y.match(&number));
    Variable Z("Z", 2);
    Structure s(new Atom("s"), {});
    ASSERT_TRUE(Z.match(&s));
}

TEST(Variable, matchAtom)
{
    Variable X("X", 0);
    Atom atom1("tom");
    Atom atom2("jerry");
    X.match(&atom1);
    ASSERT_TRUE(X.match(&atom1));
    ASSERT_FALSE(X.match(&atom2));
}

TEST(Variable, matchNumber)
{
    Variable X("X", 0);
    Number n1(-0.1);
    Number n2(0.1);
    X.match(&n1);
    ASSERT_TRUE(X.match(&n1));
    ASSERT_FALSE(X.match(&n2));
}

TEST(Variable, matchStructure)
{
    Variable X("X", 0);
    Structure s1(new Atom("s1"), {});
    Structure s2(new Atom("s2"), {});
    X.match(&s1);
    ASSERT_TRUE(X.match(&s1));
    ASSERT_FALSE(X.match(&s2));
}

TEST(Variable, matchSuccessWhenDetectingCycle)
{
    Variable X("X", 0);
    Variable Y("Y", 1);
    Variable Z("Z", 2);
    X.match(&Y);
    Y.match(&Z);
    ASSERT_TRUE(X.match(&Z));
}

TEST(Variable, matchVariableSuccess)
{
    Variable X("X", 0);
    Variable Y("Y", 1);
    Atom atom("tom");
    X.match(&atom);
    ASSERT_TRUE(X.match(&Y));
}

TEST(Variable, matchVariableFail)
{
    Variable X("X", 0);
    Variable Y("Y", 1);
    Atom atom1("tom");
    Atom atom2("jerry");
    X.match(&atom1);
    Y.match(&atom2);
    ASSERT_FALSE(X.match(&Y));
}

TEST(Variable, getStructure)
{
    Variable X("X", 0);
    ASSERT_EQ(nullptr, X.getStructure());
}

TEST(Variable, getVariable)
{
    Variable X("X", 0);
    ASSERT_EQ(&X, X.getVariable());
}

TEST(Variable, age)
{
    Variable X("X", 0);
    ASSERT_EQ(0, X.age());
}

TEST(Variable, instance)
{
    Variable X("X", 0);
    ASSERT_EQ(nullptr, X.instance());
    Atom atom("tom");
    X.match(&atom);
    ASSERT_EQ(&atom, X.instance());
}

TEST(Variable, cycleByItself)
{
    Variable X("X", 0);
    ASSERT_TRUE(X.hasCycle(&X));
}

TEST(Variable, cycleByInstance)
{
    Variable X("X", 0);
    Variable Y("Y", 1);
    X.match(&Y);
    ASSERT_TRUE(Y.match(&X));
}

TEST(Variable, matchVariable)
{
    Variable X("X", 0);
    Variable Y("Y", 1);
    Variable Z("Z", 2);
    Atom atom1("tom");
    Atom atom2("jerry");
    X.match(&atom1);
    ASSERT_TRUE(X.match(&Z));
    Y.match(&atom2);
    ASSERT_FALSE(X.match(&Y));
}

TEST(Variable, linkSharedVariables)
{
    Variable A("A", 0);
    Variable B("B", 1);
    Variable C("C", 2);
    Variable D("D", 3);
    Atom atom("tom");
    A.match(&C);
    A.match(&atom);
    D.match(&B);
    D.linkSharedVariables(D._head, A._head, &atom);
    ASSERT_EQ("A", D._head->symbol());
    ASSERT_EQ("B", A.instance()->symbol());
    ASSERT_EQ("C", B.instance()->symbol());
    ASSERT_EQ("D", C.instance()->symbol());
    ASSERT_EQ("tom", D.instance()->symbol());
}

TEST(Variable, createSharedVariables)
{
    Variable A("A", 0);
    Variable B("B", 1);
    Variable C("C", 2);
    Variable D("D", 3);
    Atom atom("tom");
    A.match(&C);
    A.match(&atom);
    D.match(&B);
    vector<Variable *> shares = D.createSharedVariables(D._head, A._head);
    string symbol[] = {"A", "B", "C", "D"};
    for (int i = 0; i < shares.size(); i++)
        ASSERT_EQ(symbol[i], shares[i]->symbol());
}

TEST(Variable, lastSharedVariable)
{
    Variable X("X", 0);
    Variable Y("Y", 1);
    Atom atom("tom");
    X.match(&Y);
    Y.match(&atom);
    ASSERT_EQ("Y", X.lastSharedVariable()->symbol());
}

TEST(Variable, convertInstanceToVariable)
{
    Variable X("X", 0);
    ASSERT_EQ(nullptr, X.convertInstanceToVariable());
    Variable Y("Y", 1);
    X.match(&Y);
    ASSERT_EQ(&Y, X.convertInstanceToVariable());
}

#endif