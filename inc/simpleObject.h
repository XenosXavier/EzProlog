#ifndef SIMPLE_OBJECT
#define SIMPLE_OBJECT
#include "term.h"

/**
 * Simple object is a term of prolog data objects.
 * It is not a compound object.
 */
class SimpleObject : public Term
{
public:
  string symbol() const;

protected:
  SimpleObject(string symbol);
  string _symbol;
};

#endif