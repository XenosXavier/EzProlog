#ifndef AND_EXP_H
#define AND_EXP_H
#include "exp.h"

class AndExp : public Exp
{
public:
  AndExp(Exp *left, Exp *right);
  bool evaluate();
};

#endif