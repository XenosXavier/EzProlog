#ifndef EXP_FACTORY_H
#define EXP_FACTORY_H
#include "matchingExp.h"
#include "andExp.h"
#include "orExp.h"

class ExpFactory
{
  public:
    MatchingExp *createMatchingExp(Term *left, Term *right);
    AndExp *createAndExp(Exp *left, Exp *right);
    OrExp *createOrExp(Exp *left, Exp *right);
};

#endif