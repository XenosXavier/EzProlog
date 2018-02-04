#include "../inc/andExp.h"

AndExp::AndExp(Exp *left, Exp *right) : Exp(","), _left(left), _right(right)
{
}

// Returns true if both expression(left and right) are true.
bool AndExp::evaluate()
{
    return (_left->evaluate() && _right->evaluate());
}