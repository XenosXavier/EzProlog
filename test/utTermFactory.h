#ifndef UT_TERM_FACTORY_H
#define UT_TERM_FACTORY_H
#include "../inc/termFactory.h"

class TermFactoryTest : public ::testing::Test
{
  public:
    TermFactory *termFactory;

  protected:
    void SetUp()
    {
        termFactory = new TermFactory();
    }
};

TEST_F(TermFactoryTest, createAtom)
{
    Atom *tom = termFactory->createAtom("tom");
    ASSERT_EQ("tom", tom->symbol());
    tom = termFactory->createAtom("tom");
    ASSERT_EQ(1, termFactory->_atomTable.size());
}

TEST_F(TermFactoryTest, createNumber)
{
    Number *n1 = termFactory->createNumber(0.1);
    ASSERT_EQ("0.1", n1->symbol());
    n1 = termFactory->createNumber(0.1);
    ASSERT_EQ(1, termFactory->_numberTable.size());
}

TEST_F(TermFactoryTest, createVariable)
{
    Variable *var = termFactory->createVariable("X");
    ASSERT_EQ("X", var->symbol());
    var = termFactory->createVariable("X");
    ASSERT_EQ(1, termFactory->_variableTable.size());
}

TEST_F(TermFactoryTest, createStructure)
{
    Atom *f = termFactory->createAtom("f");
    Atom *tom = termFactory->createAtom("tom");
    Structure *s = termFactory->createStructure(f, {tom});
    ASSERT_EQ("f(tom)", s->symbol());
    s = termFactory->createStructure(f, {tom});
    ASSERT_EQ(1, termFactory->_structureTable.size());
}

TEST_F(TermFactoryTest, createStructureException)
{
    Atom *functor = nullptr;
    Atom *arg = termFactory->createAtom("tom");
    try
    {
        Structure *s = termFactory->createStructure(functor, {arg});
        FAIL() << "It should throw 'Nonvalid functor of structure'";
    }
    catch (const string &exception)
    {
        ASSERT_EQ("Nonvalid functor of structure", exception);
    }
}

#endif