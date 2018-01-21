#include "../inc/structure.h"
// #include <stdexcept>

Structure::Structure(Atom *functor, vector<Term *> args) : _functor(functor), _args(args)
{
}

string Structure::symbol() const
{
    return output(OutputMode::symbol);
}

string Structure::value() const
{
    return output(OutputMode::value);
}

bool Structure::match(Term *term)
{
    if (term->getVariable() != nullptr)
        return term->match(this);
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

Atom *Structure::functor() const
{
    return _functor;
}

Term *Structure::arg(int index) const
{
    if (index < _args.size())
        return _args[index];
    throw string("The index of structure arugments is out of range.");
}

int Structure::arity() const
{
    return _args.size();
}

string Structure::output(OutputMode mode) const
{
    string ret = _functor->symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
        ret += ((i > 0) ? ", " : "") + argOutput(i, mode);
    return ret + ")";
}

string Structure::argOutput(int index, OutputMode mode) const
{
    if (mode == OutputMode::symbol)
        return arg(index)->symbol();
    else if (mode == OutputMode::value)
        return arg(index)->value();
    throw string("Unexpected output mode of argument");
}