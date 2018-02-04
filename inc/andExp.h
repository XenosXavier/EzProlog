#ifndef AND_EXP_H
#define AND_EXP_H
#include "exp.h"

/**  
 * [Interpreter Pattern - Nonterminal Expression]
 * AndExp is a conjunction expression. It should be 
 * true if both expressions are true on evaluating.
 */
class AndExp : public Exp
{
public:
  AndExp(Exp *left, Exp *right);
  bool evaluate();

private:
  Exp *_left;
  Exp *_right;
};

#endif