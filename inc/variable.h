#ifndef VARIABLE_H
#define VARIABLE_H
#include "simpleObject.h"
#include <gtest/gtest_prod.h>
#include <vector>
using std::vector;

/**
 * [Composite Pattern - Leaf]
 * Variable is a simple object of prolog data objects.
 * Instance can only be assigned if it is empty and the
 * matching term won't cause any cycle.
 */
class Variable : public SimpleObject
{
public:
  Variable(string symbol, int age);
  string value();
  bool match(Term *term);
  Variable *getVariable();
  int age();
  Term *instance();

private:
  FRIEND_TEST(Variable, cycleByItself);
  FRIEND_TEST(Variable, cycleByInstance);
  FRIEND_TEST(Variable, matchVariable);
  FRIEND_TEST(Variable, linkSharedVariables);
  FRIEND_TEST(Variable, createSharedVariables);
  FRIEND_TEST(Variable, lastSharedVariable);
  FRIEND_TEST(Variable, convertInstanceToVariable);

  bool hasCycle(Term *term);
  bool matchVariable(Variable *other);
  void linkSharedVariables(Variable *head, Variable *otherHead, Term *instance);
  vector<Variable *> createSharedVariables(Variable *head, Variable *otherHead);
  Variable *lastSharedVariable();
  Variable *convertInstanceToVariable();

  bool _hasVisited;
  int _age;
  Term *_instance;
  Variable *_head;
};

#endif