#ifndef UT_STRUCTURE_H
#define UT_STRUCTURE_H
#include "../inc/structure.h"
#include "../inc/number.h"
#include "../inc/variable.h"

TEST(structure, symbol)
{
    Atom functor("s");
    Atom tom("tom");
    Number num(-0.1);
    Variable X("X");
    Structure s(&functor, {&tom, &num, &X});
    ASSERT_EQ("s(tom, -0.1, X)", s.symbol());
}

TEST(structure, value)
{
    Atom functor("s");
    Atom tom("tom");
    Number num(-0.1);
    Variable X("X");
    X.match(&tom);
    Structure s(&functor, {&tom, &num, &X});
    ASSERT_EQ("s(tom, -0.1, tom)", s.value());
}

TEST(structure, nestedSymbol)
{
    // empty structure, s()
    Structure s0(new Atom("s"), {});
    // sub structure in the middle of args, s(tom, s(), jerry)
    Structure s1(new Atom("s"), {new Atom("tom"), &s0, new Atom("jerry")});
    // sub structure at the beginning of args, s(s(tom, s(), jerry), jerry)
    Structure s2(new Atom("s"), {&s1, new Atom("jerry")});
    // sub structure at the end of args, s(tom, s(s(tom, s(), jerry), jerry))
    Structure s3(new Atom("s"), {new Atom("tom"), &s2});
    ASSERT_EQ("s(tom, s(s(tom, s(), jerry), jerry))", s3.symbol());
}

TEST(structure, matchConstant)
{
    Structure s0(new Atom("s"), {});
    Atom s1("s");
    ASSERT_FALSE(s0.match(&s1));
    Number n1(-0.1);
    ASSERT_FALSE(s0.match(&n1));
}

TEST(structure, matchVariable)
{
    Structure s0(new Atom("s"), {});
    Variable X("X");
    ASSERT_TRUE(s0.match(&X));
}

TEST(structure, matchFunctor)
{
    Structure s0(new Atom("s"), {});
    Structure s1(new Atom("f"), {});
    ASSERT_FALSE(s0.match(&s1));
}

TEST(structure, matchArity)
{
    Structure s0(new Atom("s"), {new Atom("tom")});
    Structure s1(new Atom("s"), {});
    ASSERT_FALSE(s0.match(&s1));
}

TEST(structure, matchArgs)
{
    Structure s0(new Atom("s"), {new Atom("tom")});
    Structure s1(new Atom("s"), {new Atom("tim")});
    ASSERT_FALSE(s0.match(&s1));
}

TEST(structure, matchSuccess)
{
    Structure s0(new Atom("s"), {new Atom("tom")});
    Structure s1(new Atom("s"), {new Atom("tom")});
    ASSERT_TRUE(s0.match(&s1));
}

TEST(structure, getStructure)
{
    Structure s(new Atom("s"), {});
    ASSERT_TRUE(s.getStructure());
    ASSERT_EQ(&s, s.getStructure());
}

TEST(structure, getVariable)
{
    Structure s(new Atom("s"), {});
    ASSERT_FALSE(s.getVariable());
}

TEST(structure, functor)
{
    Structure s(new Atom("s"), {});
    ASSERT_EQ("s", s.functor()->symbol());
}

TEST(structure, arg)
{
    Structure s(new Atom("s"), {new Atom("tom"), new Atom("jerry")});
    ASSERT_EQ("tom", s.arg(0)->symbol());
    ASSERT_EQ("jerry", s.arg(1)->symbol());
}

TEST(structure, argException)
{
    Structure s(new Atom("s"), {});
    ASSERT_THROW(s.arg(0), std::string);
    try
    {
        s.arg(0);
        FAIL() << "It should throw 'The index of structure arugments is out of range.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("The index of structure arugments is out of range.", exception);
    }
}

TEST(structure, arity)
{
    Structure s(new Atom("s"), {new Atom("tom"), new Atom("jerry")});
    ASSERT_EQ(2, s.arity());
}

TEST(structure, output)
{
    Variable X("X");
    Atom tom("tom");
    X.match(&tom);
    Structure s(new Atom("s"), {&X});
    ASSERT_EQ("s(X)", s.output(Structure::OutputMode::symbol));
    ASSERT_EQ("s(tom)", s.output(Structure::OutputMode::value));
}

TEST(structure, argOutput)
{
    Variable X("X");
    Atom tom("tom");
    X.match(&tom);
    Structure s(new Atom("s"), {&X});
    ASSERT_EQ("X", s.argOutput(0, Structure::OutputMode::symbol));
    ASSERT_EQ("tom", s.argOutput(0, Structure::OutputMode::value));
}

#endif