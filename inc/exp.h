#ifndef EXP_H
#define EXP_H
#include <vector>
using std::vector;

template <class T>
class Iterator;
class Exp
{
public:
  virtual bool evaluate() = 0;
  int degree();
  Exp *child(int index);
  virtual Iterator<Exp *> *createIterator();
  Iterator<Exp *> *createRightRecursiveIterator();

protected:
  Exp(vector<Exp *> exps);
  vector<Exp *> _exps;
};

#endif