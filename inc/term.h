#ifndef TERM_H
#define TERM_H
#include <string>
using std::string;

class Structure;
class Variable;
class Term
{
public:
  virtual string symbol() const = 0;
  virtual string value() const = 0;
  virtual bool match(Term *term) = 0;
  virtual Structure *getStructure();
  virtual Variable *getVariable();

private:
};

#endif
