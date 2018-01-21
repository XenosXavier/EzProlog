#ifndef NUMBER_H
#define NUMBER_H
#include "constant.h"
#include <sstream>

class Number : public Constant
{
public:
  Number(double value);

private:
  string createSymbol(double value);
};

#endif