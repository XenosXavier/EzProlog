#include "../inc/matchingExp.h"

MatchingExp::MatchingExp(Term *left, Term *right) : _left(left), _right(right), Exp({})
{
}

bool MatchingExp::evaluate()
{
    return _left->match(_right);
}