#include "../inc/expBuilder.h"
#include <iostream>

ExpBuilder::ExpBuilder() : _prologUtils(PrologUtils::getInstance())
{
}

// Add a term node into node stack.
void ExpBuilder::addTermNode(Term *term)
{
    _termNodes.push(term);
}

// Try to create any expressions from operator
// and node stack before pushing new operator.
void ExpBuilder::addOperatorNode(string op)
{
    tryToCreateExpression(op);
    _opNodes.push(op);
}

// Build an expression tree from
// operator and term stack.
void ExpBuilder::buildExpTree()
{
    while (!_opNodes.empty())
        createExpression();
}

// Get the expression tree from expression stack
// if the node and operator stack are empty and
// there is only one element in expression stack.
Exp *ExpBuilder::getExpTree()
{
    if (_expTrees.size() != 1 || !_termNodes.empty() || !_opNodes.empty())
        throw string("Unexpected end of clause.");
    return _expTrees.top();
}

// Try to create any expressions from node and
// operator stack if the priority of new operator
// is greater than the top element in operator stack.
void ExpBuilder::tryToCreateExpression(string newOp)
{
    int newOpPriority = _prologUtils->getOpPriority(newOp);
    while (!_opNodes.empty() && newOpPriority > _prologUtils->getOpPriority(_opNodes.top()))
        createExpression();
}

// Create an expression from operator stack.
void ExpBuilder::createExpression()
{
    string op = extractLast(_opNodes);
    if (op == "=")
        createTerminalExp();
    else
        createNonTerminalExp(op);
}

// Create a terminal(matching) expression
// from node stack.
void ExpBuilder::createTerminalExp()
{
    Term *right = extractLast(_termNodes);
    Term *left = extractLast(_termNodes);
    _expTrees.push(_expFactory.createMatchingExp(left, right));
}

// Create a nonterminal(conjunction or disjunction)
// expression from node stack.
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

// Extract the last(top) element from stack.
template <class T>
T ExpBuilder::extractLast(stack<T> &stack)
{
    if (stack.empty())
        return {}; // Returns default value of T in C++11 compiler.
    T item = stack.top();
    stack.pop();
    return item;
}