#include "../inc/termFactory.h"
#include <sstream>

// Create an atom.
Atom *TermFactory::createAtom(string symbol)
{
    if (_atomTable.find(symbol) == _atomTable.end())
        _atomTable[symbol] = new Atom(symbol);
    return _atomTable[symbol];
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
Variable *TermFactory::createVariable(string symbol)
{
    if (_variableTable.find(symbol) == _variableTable.end())
        _variableTable[symbol] = new Variable(symbol, _variableTable.size());
    return _variableTable[symbol];
}

// create a structure.
Structure *TermFactory::createStructure(Atom *functor, vector<Term *> args)
{
    if (functor == nullptr)
        throw string("Nonvalid functor of structure");
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