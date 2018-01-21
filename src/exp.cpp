#include "../inc/exp.h"
#include "../inc/nullIterator.h"
#include "../inc/rightRecursiveIterator.h"

int Exp::degree()
{
    return _exps.size();
}

Exp *Exp::child(int index)
{
    if (index > degree())
        throw string("The child index is out of range");
    return _exps[index];
}

Iterator<Exp *> *Exp::createIterator()
{
    return new NullIterator<Exp *>();
}

Iterator<Exp *> *Exp::createRightRecursiveIterator()
{
    return new RightRecursiveIterator<Exp *>(createIterator());
}

Exp::Exp(vector<Exp *> exps) : _exps(exps)
{
}
