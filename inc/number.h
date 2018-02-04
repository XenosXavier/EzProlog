#ifndef NUMBER_H
#define NUMBER_H
#include "constant.h"
#include <sstream>

/**
 * [Composite Pattern - Leaf]
 * Number is a constant in prolog data objects.
 */
class Number : public Constant
{
public:
  Number(double value);

private:
  string createSymbol(double value);
};

#endif