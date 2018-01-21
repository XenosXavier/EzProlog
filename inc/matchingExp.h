#ifndef MATCHING_EXP_H
#define MATCHING_EXP_H
#include "exp.h"
#include "term.h"

class MatchingExp : public Exp
{
  public:
    MatchingExp(Term *left, Term *right);
    bool evaluate();

  private:
    Term *_left;
    Term *_right;
};

#endif