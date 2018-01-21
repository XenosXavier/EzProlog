#include "../inc/simpleObject.h"

string SimpleObject::symbol() const
{
    return _symbol;
}

SimpleObject::SimpleObject(string symbol) : _symbol(symbol)
{
}