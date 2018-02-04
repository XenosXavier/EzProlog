#include "../inc/orExp.h"
#include "../inc/orExpIterator.h"

OrExp::OrExp(Exp *left, Exp *right) : Exp(";"), _left(left), _right(right)
{
}

// Returns true if any expression(left or right) is true.
bool OrExp::evaluate()
{
    return (_left->evaluate() || _right->evaluate());
}

// Create an OrExpIterator.
Iterator<Exp *> *OrExp::createIterator()
{
    return new OrExpIterator(this);
}

// Get the left expression.
Exp *OrExp::left()
{
    return _left;
}

// Get the right expression.
Exp *OrExp::right()
{
    return _right;
}