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
  FRIEND_TEST(expBuilder, addTermNode);
  FRIEND_TEST(expBuilder, addOperatorNode);
  FRIEND_TEST(expBuilder, buildExpTree);
  FRIEND_TEST(expBuilder, getExpTree);
  FRIEND_TEST(expBuilder, tryToCreateExpression);
  FRIEND_TEST(expBuilder, createMatchingExpression);
  FRIEND_TEST(expBuilder, createAndExpression);
  FRIEND_TEST(expBuilder, createOrExpression);
  FRIEND_TEST(expBuilder, stackException);

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