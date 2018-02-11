#ifndef EXP_BUILDER_H
#define EXP_BUILDER_H
#include "prologUtils.h"
#include "expFactory.h"
#include "term.h"
#include <stack>
#include <gtest/gtest_prod.h>
using std::stack;

/**
 * [Builder Pattern - Builder]
 * This is a bottom-up expression builder. 
 * It will try to create a tail recursion expression tree 
 * in buildExpTree and get the result from the getExpTree.
 */
class ExpBuilder
{
public:
  ExpBuilder();
  void addTermNode(Term *term);
  void addOperatorNode(string op);
  void buildExpTree();
  Exp *getExpTree();

private:
  FRIEND_TEST(ExpBuilder, addTermNode);
  FRIEND_TEST(ExpBuilder, addOperatorNode);
  FRIEND_TEST(ExpBuilder, buildExpTree);
  FRIEND_TEST(ExpBuilder, getExpTree);
  FRIEND_TEST(ExpBuilder, tryToCreateExpression);
  FRIEND_TEST(ExpBuilder, createMatchingExpression);
  FRIEND_TEST(ExpBuilder, createAndExpression);
  FRIEND_TEST(ExpBuilder, createOrExpression);
  FRIEND_TEST(ExpBuilder, stackException);

  void tryToCreateExpression(string newOp);
  void createExpression();
  void createTerminalExp();
  void createNonTerminalExp(string op);
  template <class T>
  T extractLast(stack<T> &stack);

  stack<Term *> _termNodes;
  stack<string> _opNodes;
  stack<Exp *> _expTrees;
  ExpFactory _expFactory;
  PrologUtils *_prologUtils;
};

#endif