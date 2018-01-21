#include "../inc/variable.h"

Variable::Variable(string symbol) : SimpleObject(symbol), _instance(nullptr)
{
}

string Variable::value() const
{
    if (_instance != nullptr)
        return _instance->value();
    return _symbol;
}

bool Variable::match(Term *term)
{
    if (_instance != nullptr)
        return _instance->match(term);
    if (term != this)
        _instance = term;
    return true;
}

Variable *Variable::getVariable()
{
    return this;
}

Term *Variable::instance()
{
    return _instance;
}