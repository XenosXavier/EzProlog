#ifndef UT_OR_EXP_ITERATOR_H
#define UT_OR_EXP_ITERATOR_H
#include "../inc/scanner.h"
#include "../inc/parser.h"
#include "../inc/expBuilder.h"
#include "../inc/iterator.h"

class OrExpIteratorTest : public ::testing::Test
{
  public:
    ExpBuilder expBuilder;

  protected:
    void SetUp()
    {
        Scanner scanner("X=1;2=1.");
        Parser parser(scanner, expBuilder);
        parser.parse();
    }
};

TEST_F(OrExpIteratorTest, first)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *it = expTree->createIterator();
    it->first();
    ASSERT_TRUE(it->currentItem()->evaluate());
}

TEST_F(OrExpIteratorTest, next)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *it = expTree->createIterator();
    it->first();
    it->next();
    ASSERT_FALSE(it->currentItem()->evaluate());
}

TEST_F(OrExpIteratorTest, isDone)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *it = expTree->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(OrExpIteratorTest, currentItem)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *it = expTree->createIterator();
    it->first();
    ASSERT_TRUE(it->currentItem()->evaluate());
    it->next();
    ASSERT_FALSE(it->currentItem()->evaluate());
}

#endif