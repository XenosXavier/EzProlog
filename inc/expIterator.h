#ifndef EXP_ITERATOR_H
#define EXP_ITERATOR_H
#include "iterator.h"
#include "exp.h"

class ExpIterator : public Iterator<Exp *>
{
  public:
    ExpIterator(Exp *exp) : _exp(exp), _index(0)
    {
    }

    void first()
    {
        _index = 0;
    }

    void next()
    {
        _index++;
    }

    bool isDone() const
    {
        return (_index >= _exp->degree());
    }

    Exp *currentItem() const
    {
        if (isDone())
            return nullptr;
        return _exp->child(_index);
    }

  private:
    Exp *_exp;
    int _index;
};

#endif