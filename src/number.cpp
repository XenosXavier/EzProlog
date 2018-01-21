#include "../inc/number.h"

Number::Number(double value) : Constant(createSymbol(value))
{
}

string Number::createSymbol(double value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}