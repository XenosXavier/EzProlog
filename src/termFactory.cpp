#include "../inc/termFactory.h"
#include <sstream>

// Create an atom.
Atom *TermFactory::createAtom(string key)
{
    if (_atomTable.find(key) == _atomTable.end())
        _atomTable[key] = new Atom(key);
    return _atomTable[key];
}

// Create a number.
Number *TermFactory::createNumber(double value)
{
    std::stringstream ss;
    ss << value;
    string key = ss.str(); // convert double to string(key)
    if (_numberTable.find(key) == _numberTable.end())
        _numberTable[key] = new Number(value);
    return _numberTable[key];
}

// Create a variable.
Variable *TermFactory::createVariable(string key)
{
    if (_variableTable.find(key) == _variableTable.end())
        _variableTable[key] = new Variable(key);
    return _variableTable[key];
}

// create a structure.
Structure *TermFactory::createStructure(Atom *functor, vector<Term *> args)
{
    string key = functor->symbol();
    for (int i = 0; i < args.size(); i++)
        key += ((i > 0) ? "," : "|") + args[i]->symbol();
    if (_structureTable.find(key) == _structureTable.end())
        _structureTable[key] = new Structure(functor, args);
    return _structureTable[key];
}

// Return the variable table.
map<string, Variable *> TermFactory::variableTable()
{
    return _variableTable;
}

TermFactory::TermFactory()
{
}