#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "atom.h"
#include <vector>
#include <gtest/gtest_prod.h>
using std::vector;

class Structure : public Term
{
public:
  Structure(Atom *functor, vector<Term *> args);
  string symbol() const;
  string value() const;
  bool match(Term *term);
  Structure *getStructure();
  Atom *functor() const;
  Term *arg(int index) const;
  int arity() const;

private:
  FRIEND_TEST(structure, output);
  FRIEND_TEST(structure, argOutput);
  enum class OutputMode
  {
    symbol,
    value
  };

  string output(OutputMode mode) const;
  string argOutput(int index, OutputMode mode) const;
  Atom *_functor;
  vector<Term *> _args;
};

#endif