#ifndef CONSTANT_H
#define CONSTANT_H
#include "simpleObject.h"

class Constant : public SimpleObject
{
public:
  string value() const;
  bool match(Term *term);

protected:
  Constant(string symbol);
};

#endif