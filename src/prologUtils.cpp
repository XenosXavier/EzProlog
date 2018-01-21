#include "../inc/prologUtils.h"

PrologUtils *PrologUtils::_instance = nullptr;

PrologUtils *PrologUtils::getInstance()
{
    if (_instance == nullptr)
        _instance = new PrologUtils();
    return _instance;
}

bool PrologUtils::isSpecialChar(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '.' || c == '&' || c == '\\' || c == '~' || c == '^' || c == '$' || c == '#' || c == '@' || c == '?' || c == ':';
}

bool PrologUtils::isOperator(string op)
{
    return (_opPriorityTable.find(op) != _opPriorityTable.end());
}

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