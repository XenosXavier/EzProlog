#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H
#include "iterator.h"

template <class T>
class NullIterator : public Iterator<T>
{
  public:
    void first()
    {
    }

    void next()
    {
    }

    bool isDone() const
    {
        return true;
    }

    T currentItem() const
    {
        throw string("Invalid item from null iterator");
    }
};

#endif