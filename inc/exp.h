#ifndef EXP_H
#define EXP_H
#include <string>
#include <vector>
using std::string;
using std::vector;

/**
 * [Interpreter Pattern - Abstract Expression]
 * The abstract class of expression. Provide an
 * interface 'evaluate' to get the result from
 * prolog expression.
 */
template <class T>
class Iterator;
class Exp
{
public:
  virtual bool evaluate() = 0;
  string symbol();
  virtual Iterator<Exp *> *createIterator();
  Iterator<Exp *> *createClauseIterator();

protected:
  Exp(string symbol);

private:
  string _symbol;
};

#endif