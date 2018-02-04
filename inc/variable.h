#ifndef VARIABLE_H
#define VARIABLE_H
#include "simpleObject.h"
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
  Variable(string symbol);
  string value();
  bool match(Term *term);
  bool hasCycle(Term *term);
  bool matchVariable(Variable *other);
  void linkSharedVariables(Variable *myHead, Variable *otherHead, Term *instance);
  vector<Variable *> createSharedVariables(Variable *head, Variable *otherHead);
  Variable *lastSharedVariable();
  Variable *getVariable();
  Variable *convertInstanceToVariable();
  Term *instance();

private:
  bool _hasVisited;
  Term *_instance;
  Variable *_head;
};

#endif