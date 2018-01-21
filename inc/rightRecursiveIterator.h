#ifndef CLAUSE_ITERATOR_H
#define CLAUSE_ITERATOR_H
#include "iterator.h"
#include <iostream>

template <class T>
class RightRecursiveIterator : public Iterator<T>
{
  public:
    RightRecursiveIterator(Iterator<T> *root) : _root(root), _current(root)
    {
    }

    void first()
    {
        _root->first();
        _current = _root;
    }

    void next()
    {
        _current->next();
        if (_current->isDone())
            return;
        Iterator<T> *next = _current->currentItem()->createIterator();
        if (!next->isDone())
            _current = next;
    }

    bool isDone() const
    {
        return _current->isDone();
    }

    T currentItem() const
    {
        return _current->currentItem();
    }

  private:
    Iterator<T> *_root;
    Iterator<T> *_current;
};

#endif