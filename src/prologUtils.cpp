#include "../inc/prologUtils.h"

PrologUtils *PrologUtils::_instance = nullptr;

// Get the singleton instance.
PrologUtils *PrologUtils::getInstance()
{
    if (_instance == nullptr) // Create a utility if instance is null.
        _instance = new PrologUtils();
    return _instance;
}

// Returns true if it is a special character.
bool PrologUtils::isSpecialChar(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '.' || c == '&' || c == '\\' || c == '~' || c == '^' || c == '$' || c == '#' || c == '@' || c == '?' || c == ':';
}

// Returns true if op is contained in operator table.
bool PrologUtils::isOperator(string op)
{
    return (_opPriorityTable.find(op) != _opPriorityTable.end());
}

// Get the operator priority.
int PrologUtils::getOpPriority(string op)
{
    if (isOperator(op))
        return _opPriorityTable[op];
    return -1;
}

PrologUtils::PrologUtils()
{
    _opPriorityTable["="] = 700;
    _opPriorityTable[","] = 1000;
    _opPriorityTable[";"] = 1100;
}