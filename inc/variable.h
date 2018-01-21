#ifndef VARIABLE_H
#define VARIABLE_H
#include "simpleObject.h"

class Variable : public SimpleObject
{
public:
  Variable(string symbol);
  string value() const;
  bool match(Term *term);
  Variable *getVariable();
  Term *instance();

private:
  Term *_instance;
};

#endif