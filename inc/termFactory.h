#ifndef TERM_FACTORY_H
#define TERM_FACTORY_H
#include "structure.h"
#include "number.h"
#include "variable.h"
#include <map>
#include <gtest/gtest_prod.h>
using std::map;

class TermFactory
{
  friend class Parser;
  friend class TermFactoryTest;

public:
  Atom *createAtom(string key);
  Number *createNumber(double value);
  Variable *createVariable(string key);
  Structure *createStructure(Atom *functor, vector<Term *> args);
  map<string, Variable *> variableTable();

protected:
  TermFactory();

private:
  FRIEND_TEST(TermFactoryTest, createAtom);
  FRIEND_TEST(TermFactoryTest, createNumber);
  FRIEND_TEST(TermFactoryTest, createVariable);
  FRIEND_TEST(TermFactoryTest, createStructure);

  map<string, Atom *> _atomTable;
  map<string, Number *> _numberTable;
  map<string, Variable *> _variableTable;
  map<string, Structure *> _structureTable;
};

#endif