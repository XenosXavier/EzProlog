#include "../inc/constant.h"

// The symbol is also its value.
string Constant::value()
{
    return _symbol;
}

// Returns the result of variable matching if the term
// is variable, otherwise returns true if its value is
// equal to the term value.
bool Constant::match(Term *term)
{
    if (term->getVariable() != nullptr) // Use variable matching if term is variable
        return term->match(this);
    return value() == term->value(); // Returns true if both value are same
}

Constant::Constant(string symbol) : SimpleObject(symbol)
{
}