#include "../inc/matchingExp.h"

MatchingExp::MatchingExp(Term *left, Term *right) : Exp("="), _left(left), _right(right)
{
}

// Returns true if left one is equal to right one.
bool MatchingExp::evaluate()
{
    return _left->match(_right);
}