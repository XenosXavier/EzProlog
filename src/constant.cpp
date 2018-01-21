#include "../inc/constant.h"

string Constant::value() const
{
    return _symbol;
}

bool Constant::match(Term *term)
{
    if (term->getVariable() != nullptr)
        return term->match(this);
    return value() == term->value();
}

Constant::Constant(string symbol) : SimpleObject(symbol)
{
}