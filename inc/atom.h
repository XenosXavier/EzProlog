#ifndef ATOM_H
#define ATOM_H
#include "constant.h"

/**
 * [Composite Pattern - Leaf]
 * Atom is a constant in prolog data objects.
 */
class Atom : public Constant
{
public:
  Atom(string symbol);
};

#endif