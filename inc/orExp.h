#ifndef OR_EXP_H
#define OR_EXP_H
#include "exp.h"

/**
 * [Interpreter Pattern - Nonterminal Expression]
 * AndExp is a disjunction expression. It should be 
 * true if any expression is true on evaluating.
 */
class OrExp : public Exp
{
public:
  OrExp(Exp *left, Exp *right);
  bool evaluate();
  Iterator<Exp *> *createIterator();
  Exp *left();
  Exp *right();

private:
  Exp *_left;
  Exp *_right;
};

#endif