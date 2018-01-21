#include "../inc/andExp.h"

AndExp::AndExp(Exp *left, Exp *right) : Exp({left, right})
{
}

bool AndExp::evaluate()
{
    return (_exps[0]->evaluate() && _exps[1]->evaluate());
}