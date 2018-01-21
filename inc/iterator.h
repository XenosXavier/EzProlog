#ifndef ITERATOR_H
#define ITERATOR_H
#include <string>
using std::string;

template <class T>
class Iterator
{
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual T currentItem() const = 0;
};

#endif