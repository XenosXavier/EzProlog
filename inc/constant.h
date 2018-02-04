#ifndef CONSTANT_H
#define CONSTANT_H
#include "simpleObject.h"

/**
 * Constant is a simple object in prolog data objects.
 */
class Constant : public SimpleObject
{
public:
  string value();
  bool match(Term *term);

protected:
  Constant(string symbol);
};

#endif