#include "../inc/variable.h"
#include <vector>
#include <algorithm>
#include <iostream>

Variable::Variable(string symbol, int age) : SimpleObject(symbol), _hasVisited(false), _age(age), _instance(nullptr), _head(this)
{
}

// Return value.
string Variable::value()
{
    if (_hasVisited) // Return symbol if it has been visited before.
        return lastSharedVariable()->symbol();
    if (_instance != nullptr)
    {
        // Set visited to true to prevent cycle. Example: X = s(X).
        _hasVisited = true;
        string value = _instance->value();
        _hasVisited = false;
        return value;
    }
    return _symbol;
}

// Returns true if match scuccess.
bool Variable::match(Term *term)
{
    if (hasCycle(term)) // Returns true if detect any cycle.
        return true;
    else if (term->getVariable() != nullptr) // Returns matchVariable result.
        return matchVariable(term->getVariable());
    else if (_instance != nullptr) // Returns instance matching result.
        return _instance->match(term);
    else // Assign instance to matching term.
        _instance = term;
    return true;
}

Variable *Variable::getVariable()
{
    return this;
}

int Variable::age()
{
    return _age;
}

// Get instance.
Term *Variable::instance()
{
    return _instance;
}

// Returns true if detect any cycle.
// Exmaple: X = Y, Y = X.
bool Variable::hasCycle(Term *term)
{
    Variable *other = term->getVariable();
    for (; other != nullptr; other = other->convertInstanceToVariable())
        if (other == this)
            return true;
    return false;
}

// Returns ture if match success with another variable.
bool Variable::matchVariable(Variable *other)
{
    Term *instance = lastSharedVariable()->instance();
    Term *otherInstance = other->lastSharedVariable()->instance();
    if (instance != nullptr && otherInstance != nullptr) // Match both instance.
        return instance->match(otherInstance);
    linkSharedVariables(_head, other->_head, (instance != nullptr) ? instance : otherInstance);
    return true;
}

// Link the shard variables and order by their address
void Variable::linkSharedVariables(Variable *head, Variable *otherHead, Term *instance)
{
    vector<Variable *> shares = createSharedVariables(head, otherHead);
    for (int i = 0, count = shares.size(); i < count; i++)
    {
        shares[i]->_head = shares[0]; // Remember the first one.
        shares[i]->_instance = ((i + 1 < count) ? shares[i + 1] : instance);
    }
}

// Create the shared variables.
vector<Variable *> Variable::createSharedVariables(Variable *head, Variable *otherHead)
{
    vector<Variable *> shares;
    for (; head != nullptr; head = head->convertInstanceToVariable())
        shares.push_back(head);
    for (; otherHead != nullptr; otherHead = otherHead->convertInstanceToVariable())
        shares.push_back(otherHead);
    // Sort the share variables by address.
    std::sort(shares.begin(), shares.end(), [](Variable *a, Variable *b) {
        return a->age() < b->age();
    });
    return shares;
}

// Get last variable.
Variable *Variable::lastSharedVariable()
{
    Variable *lastOne = this;
    while (lastOne->convertInstanceToVariable() != nullptr)
        lastOne = lastOne->convertInstanceToVariable();
    return lastOne;
}

// Convert self instance to variable.
Variable *Variable::convertInstanceToVariable()
{
    if (_instance == nullptr)
        return nullptr;
    return _instance->getVariable();
}