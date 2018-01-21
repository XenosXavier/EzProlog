#include "../inc/orExp.h"
#include "../inc/expIterator.h"

OrExp::OrExp(Exp *left, Exp *right) : Exp({left, right})
{
}

bool OrExp::evaluate()
{
    return (_exps[0]->evaluate() || _exps[1]->evaluate());
}

Iterator<Exp *> *OrExp::createIterator()
{
    return new ExpIterator(this);
}