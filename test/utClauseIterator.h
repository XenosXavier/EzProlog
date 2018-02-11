#ifndef UT_CLAUSE_ITERATOR_H
#define UT_CLAUSE_ITERATOR_H
#include "../inc/scanner.h"
#include "../inc/parser.h"
#include "../inc/expBuilder.h"
#include "../inc/iterator.h"

class ClauseIteratorTest : public ::testing::Test
{
  public:
    ExpBuilder expBuilder;

  protected:
    void SetUp()
    {
        Scanner scanner("X=1,Y=2;Z=3;1=3,Q=5.");
        Parser parser(scanner, expBuilder);
        parser.parse();
    }
};

TEST_F(ClauseIteratorTest, first)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *clauseIterator = expTree->createClauseIterator();
    clauseIterator->first();
    ASSERT_TRUE(clauseIterator->currentItem()->evaluate());
}

TEST_F(ClauseIteratorTest, next)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *clauseIterator = expTree->createClauseIterator();
    clauseIterator->first();
    ASSERT_TRUE(clauseIterator->currentItem()->evaluate());
    clauseIterator->next();
    ASSERT_TRUE(clauseIterator->currentItem()->evaluate());
    clauseIterator->next();
    ASSERT_FALSE(clauseIterator->currentItem()->evaluate());
}

TEST_F(ClauseIteratorTest, isDone)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *clauseIterator = expTree->createClauseIterator();
    clauseIterator->first();
    ASSERT_FALSE(clauseIterator->isDone());
    clauseIterator->next();
    ASSERT_FALSE(clauseIterator->isDone());
    clauseIterator->next();
    ASSERT_FALSE(clauseIterator->isDone());
    clauseIterator->next();
    ASSERT_TRUE(clauseIterator->isDone());
}

TEST_F(ClauseIteratorTest, currentItem)
{
    Exp *expTree = expBuilder.getExpTree();
    Iterator<Exp *> *clauseIterator = expTree->createClauseIterator();
    clauseIterator->first();
    ASSERT_TRUE(clauseIterator->currentItem()->evaluate());
    clauseIterator->next();
    ASSERT_TRUE(clauseIterator->currentItem()->evaluate());
    clauseIterator->next();
    ASSERT_FALSE(clauseIterator->currentItem()->evaluate());
}

#endif