#ifndef ITERATOR_H
#define ITERATOR_H
#include <string>
using std::string;

/**
 * [Iterator Pattern]
 * The interface of iterator.
 */
template <class T>
class Iterator
{
public:
  // Reset to first element of container.
  virtual void first() = 0;

  // Move to next element of container.
  virtual void next() = 0;

  // Returns true if all element has been iterated.
  virtual bool isDone() const = 0;

  // Get the current element from container.
  virtual T currentItem() const = 0;
};

#endif