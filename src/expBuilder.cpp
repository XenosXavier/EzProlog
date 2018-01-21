#include "../inc/expBuilder.h"
#include <iostream>

ExpBuilder::ExpBuilder() : _prologUtils(PrologUtils::getInstance())
{
}

void ExpBuilder::addTermNode(Term *term)
{
    _termNodes.push(term);
}

void ExpBuilder::addOperatorNode(string op)
{
    tryToCreateExpression(op);
    _opNodes.push(op);
}

void ExpBuilder::buildExpTree()
{
    while (!_opNodes.empty())
        createExpression();
}

Exp *ExpBuilder::getExpTree()
{
    if (_expTrees.size() != 1 || !_termNodes.empty() || !_opNodes.empty())
        throw string("Unexpected end of clause.");
    return _expTrees.top();
}

void ExpBuilder::tryToCreateExpression(string newOp)
{
    int newOpPriority = _prologUtils->getOpPriority(newOp);
    while (!_opNodes.empty() && newOpPriority > _prologUtils->getOpPriority(_opNodes.top()))
        createExpression();
}

void ExpBuilder::createExpression()
{
    string op = extractLast(_opNodes);
    if (op == "=")
        createTerminalExp();
    else
        createNonTerminalExp(op);
}

void ExpBuilder::createTerminalExp()
{
    Term *right = extractLast(_termNodes);
    Term *left = extractLast(_termNodes);
    _expTrees.push(_expFactory.createMatchingExp(left, right));
}

void ExpBuilder::createNonTerminalExp(string op)
{
    Exp *right = extractLast(_expTrees);
    Exp *left = extractLast(_expTrees);
    if (op == ",")
        _expTrees.push(_expFactory.createAndExp(left, right));
    else if (op == ";")
        _expTrees.push(_expFactory.createOrExp(left, right));
    else
        throw string("Undefined operator " + op + ".");
}

template <class T>
T ExpBuilder::extractLast(stack<T> &stack)
{
    if (stack.empty())
        return {}; // amazing default value of T in C++11
    T item = stack.top();
    stack.pop();
    return item;
}