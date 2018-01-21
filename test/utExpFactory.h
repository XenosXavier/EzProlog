#ifndef UT_EXP_FACTORY_H
#define UT_EXP_FACTORY_H
#include "../inc/expFactory.h"
#include "../inc/atom.h"

TEST(expFactory, matchingExpException)
{
    ExpFactory expFactory;
    try
    {
        expFactory.createMatchingExp(nullptr, nullptr);
        FAIL() << "It should throw 'Missing term before '='.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Missing term before '='.", exception);
    }

    try
    {
        expFactory.createMatchingExp(new Atom("tom"), nullptr);
        FAIL() << "It should throw 'Missing term after '='.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Missing term after '='.", exception);
    }
}

TEST(expFactory, andExpException)
{
    ExpFactory expFactory;
    try
    {
        expFactory.createAndExp(nullptr, nullptr);
        FAIL() << "It should throw 'Missing expression before ','.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Missing expression before ','.", exception);
    }

    try
    {
        MatchingExp *m = new MatchingExp(new Atom("tom"), new Atom("tom"));
        expFactory.createAndExp(m, nullptr);
        FAIL() << "It should throw 'Missing expression after ','.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Missing expression after ','.", exception);
    }
}

TEST(expFactory, orExpException)
{
    ExpFactory expFactory;
    try
    {
        expFactory.createOrExp(nullptr, nullptr);
        FAIL() << "It should throw 'Missing expression before ';'.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Missing expression before ';'.", exception);
    }

    try
    {
        MatchingExp *m = new MatchingExp(new Atom("tom"), new Atom("tom"));
        expFactory.createOrExp(m, nullptr);
        FAIL() << "It should throw 'Missing expression after ';'.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Missing expression after ';'.", exception);
    }
}

#endif