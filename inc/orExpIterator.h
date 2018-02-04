#ifndef OR_EXP_ITERATOR
#define OR_EXP_ITERATOR
#include "iterator.h"
#include "orExp.h"

/**
 * [Iterator Pattern]
 * Iterator all expressions in disjunction(or) expression.
 */
class OrExpIterator : public Iterator<Exp *>
{
    friend class OrExp;

  public:
    // Reset the selected expression to first one.
    void first()
    {
        _index = 0;
    }

    // Move to next expression.
    void next()
    {
        _index++;
    }

    // Returns true if the index is more than two.
    // Because a disjunction expressions only has
    // two expression, left and right.
    bool isDone() const
    {
        return (_index >= 2);
    }

    // Return the current expression from disjunction expression.
    Exp *currentItem() const
    {
        if (isDone())
            return nullptr;
        return (_index == 0) ? _orExp->left() : _orExp->right();
    }

  protected:
    OrExpIterator(OrExp *orExp) : _orExp(orExp), _index(0)
    {
    }

  private:
    OrExp *_orExp;
    int _index;
};

#endif