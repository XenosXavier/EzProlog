#ifndef MATCHING_EXP_H
#define MATCHING_EXP_H
#include "exp.h"
#include "term.h"

/**
 * [Interpreter Pattern - Terminal Expression]
 * MatchingExp is an expression to compare if
 * the left term is equal to right term.
 */
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