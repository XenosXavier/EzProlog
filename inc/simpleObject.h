#ifndef SIMPLE_OBJECT
#define SIMPLE_OBJECT
#include "term.h"

class SimpleObject : public Term
{
public:
  string symbol() const;

protected:
  SimpleObject(string symbol);
  string _symbol;
};

#endif