#ifndef UT_EXP_FACTORY_H
#define UT_EXP_FACTORY_H
#include "../inc/expFactory.h"
#include "../inc/atom.h"

TEST(ExpFactory, matchingExpException)
{
    ExpFactory expFactory;
    try
    {
        expFactory.createMatchingExp(nullptr, nullptr);
        FAIL() << "It should throw 'Uncompleted matching expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted matching expression", exception);
    }

    try
    {
        expFactory.createMatchingExp(new Atom("tom"), nullptr);
        FAIL() << "It should throw 'Uncompleted matching expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted matching expression", exception);
    }

    try
    {
        expFactory.createMatchingExp(nullptr, new Atom("tom"));
        FAIL() << "It should throw 'Uncompleted matching expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted matching expression", exception);
    }
}

TEST(ExpFactory, andExpException)
{
    ExpFactory expFactory;
    try
    {
        expFactory.createAndExp(nullptr, nullptr);
        FAIL() << "It should throw 'Uncompleted conjunction expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted conjunction expression", exception);
    }

    try
    {
        expFactory.createAndExp(new MatchingExp(new Atom("a"), new Atom("b")), nullptr);
        FAIL() << "It should throw 'Uncompleted conjunction expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted conjunction expression", exception);
    }

    try
    {
        expFactory.createAndExp(nullptr, new MatchingExp(new Atom("a"), new Atom("b")));
        FAIL() << "It should throw 'Uncompleted conjunction expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted conjunction expression", exception);
    }
}

TEST(ExpFactory, orExpException)
{
    ExpFactory expFactory;
    try
    {
        expFactory.createOrExp(new MatchingExp(new Atom("a"), new Atom("b")), nullptr);
        FAIL() << "It should throw 'Uncompleted disjunction expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted disjunction expression", exception);
    }

    try
    {
        expFactory.createOrExp(nullptr, new MatchingExp(new Atom("a"), new Atom("b")));
        FAIL() << "It should throw 'Uncompleted disjunction expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted disjunction expression", exception);
    }

    try
    {
        expFactory.createOrExp(nullptr, nullptr);
        FAIL() << "It should throw 'Uncompleted disjunction expression'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Uncompleted disjunction expression", exception);
    }
}

#endif