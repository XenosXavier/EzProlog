#ifndef CLAUSE_ITERATOR_H
#define CLAUSE_ITERATOR_H
#include "iterator.h"

/**
 * [Iterator Pattern]
 * Iterate the prolog clause. A prolog clause is 
 * an sub expression of disjunction expression.
 */
class ClauseIterator : public Iterator<Exp *>
{
  public:
    ClauseIterator(Iterator<Exp *> *root) : _root(root), _current(root)
    {
    }

    // Reset the current iterator to root.
    void first()
    {
        _root->first();
        _current = _root;
    }

    // Move the current iterator to next position.
    // Change the current iterator to the current
    // item if the symbol is ';'. Because it means
    // we travel to another disjunction expression.
    void next()
    {
        _current->next();
        if (!isDone() && _current->currentItem()->symbol() == ";")
            _current = _current->currentItem()->createIterator();
    }

    // Return true if the current iterator is done.
    bool isDone() const
    {
        return _current->isDone();
    }

    // Get the current item from the current iterator.
    Exp *currentItem() const
    {
        return _current->currentItem();
    }

  private:
    Iterator<Exp *> *_root;
    Iterator<Exp *> *_current;
};

#endif