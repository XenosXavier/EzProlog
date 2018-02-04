#include "../inc/exp.h"
#include "../inc/nullIterator.h"
#include "../inc/clauseIterator.h"

// Returns the symbol(operator) of this expression.
string Exp::symbol()
{
    return _symbol;
}

// Create an iterator for this expression.
Iterator<Exp *> *Exp::createIterator()
{
    return new NullIterator<Exp *>();
}

// Create an clause iterator for this expression.
Iterator<Exp *> *Exp::createClauseIterator()
{
    return new ClauseIterator(createIterator());
}

Exp::Exp(string symbol) : _symbol(symbol)
{
}