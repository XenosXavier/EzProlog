#include "../inc/structure.h"

Structure::Structure(Atom *functor, vector<Term *> args) : _functor(functor), _args(args)
{
}

string Structure::symbol() const
{
    return output(OutputMode::symbol);
}

string Structure::value()
{
    return output(OutputMode::value);
}

// Returns true if match scuccess.
bool Structure::match(Term *term)
{
    // Use variable matching if term is variable.
    if (term->getVariable() != nullptr)
        return term->match(this);

    // Structure can only match with another structure.
    // It will return true if both structures have the
    // same functor, size of arugment, and each matching
    // of arugments is true.
    Structure *structure = term->getStructure();
    if (structure == nullptr || arity() != structure->arity() || !_functor->match(structure->_functor))
        return false;
    for (int i = 0; i < _args.size(); i++)
        if (!_args[i]->match(structure->_args[i]))
            return false;
    return true;
}

Structure *Structure::getStructure()
{
    return this;
}

// Get functor.
Atom *Structure::functor() const
{
    return _functor;
}

// Get the argument by index.
Term *Structure::arg(int index) const
{
    if (index < _args.size())
        return _args[index];
    throw string("The index of structure arugments is out of range.");
}

// Get the size of arugment.
int Structure::arity() const
{
    return _args.size();
}

// Show the symbol or value of this structure.
string Structure::output(OutputMode mode) const
{
    string ret = _functor->symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
        ret += ((i > 0) ? ", " : "") + argOutput(i, mode);
    return ret + ")";
}

// Show the symbol or value of argument.
string Structure::argOutput(int index, OutputMode mode) const
{
    if (mode == OutputMode::symbol) // Returns symbol if mode is symbol.
        return arg(index)->symbol();
    else if (mode == OutputMode::value) // Returns value if mode is value.
        return arg(index)->value();
    throw string("Unexpected output mode of argument");
}