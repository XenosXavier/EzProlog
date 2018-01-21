#ifndef OR_EXP_H
#define OR_EXP_H
#include "exp.h"

class OrExp : public Exp
{
public:
  OrExp(Exp *left, Exp *right);
  bool evaluate();
  Iterator<Exp *> *createIterator();
};

#endif