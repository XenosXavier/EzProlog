#include "../inc/parser.h"
#include <algorithm>
#include <iostream>

Parser::Parser(Scanner &scanner, ExpBuilder &expBuilder) : _scanner(scanner), _expBuilder(expBuilder), _prologUtils(PrologUtils::getInstance())
{
    _termTokens = {_prologUtils->ATOM, _prologUtils->NUMBER, _prologUtils->VAR, '['};
    createTermFactory();
}

void Parser::parse()
{
    for (updateToken(); _token.first != '.' && _token.first != _prologUtils->EOS; updateToken())
    {
        if (isTermToken())
            _expBuilder.addTermNode(createTerm());
        else if (_prologUtils->isOperator(_token.second))
        {
            if (_token.first == ';')
                createTermFactory();
            _expBuilder.addOperatorNode(_token.second);
        }
        else
            throw string("Undefined token " + _token.second + ".");
    }
    if (_token.first != '.')
        throw string("Missing token '.' at the end of clause.");
    _expBuilder.buildExpTree();
}

vector<Variable *> Parser::clauseVariables(int index)
{
    if (index >= _termFactories.size())
        throw string("The index is out of clause size");
    map<string, Variable *> variableTable = _termFactories[index]->variableTable();
    vector<Variable *> variables;
    std::transform(variableTable.begin(), variableTable.end(), std::back_inserter(variables), [](pair<string, Variable *> const &pair) {
        return pair.second;
    });
    return variables;
}

void Parser::createTermFactory()
{
    _termFactory = new TermFactory();
    _termFactories.push_back(_termFactory);
}

void Parser::updateToken()
{
    _token = _scanner.nextToken();
}

Term *Parser::createTerm()
{
    if (_token.first == _prologUtils->ATOM)
        return createAtomOrCompound();
    else if (_token.first == _prologUtils->NUMBER)
        return _termFactory->createNumber(stod(_token.second));
    else if (_token.first == _prologUtils->VAR)
        return _termFactory->createVariable(_token.second);
    else if (_token.first == '[')
        return createBracketsCompound();
    else
        return nullptr;
}

Term *Parser::createAtomOrCompound()
{
    Atom *atom = _termFactory->createAtom(_token.second);
    if (_scanner.currentChar() == '(')
        return createParenthesesCompound(atom);
    return atom;
}

Term *Parser::createParenthesesCompound(Atom *functor)
{
    updateToken(); // move to left parentheses
    vector<Term *> args = createArgs();
    if (_token.first == ')')
        return _termFactory->createStructure(functor, args);
    throw string("Unexpected " + _token.second + " before ')'.");
}

Term *Parser::createBracketsCompound()
{
    vector<Term *> args = createArgs();
    Term *tail = createTail();
    if (_token.first == ']')
    {
        Atom *functor = _termFactory->createAtom(".");
        for (int i = args.size() - 1; i >= 0; i--)
            tail = _termFactory->createStructure(functor, {args[i], tail});
        return tail;
    }
    throw string("Unexpected " + _token.second + " before ']'.");
}

vector<Term *> Parser::createArgs()
{
    vector<Term *> args;
    // first update for extracting left parentheses or brackets
    for (updateToken(); hasNextArg(); updateToken())
        if (isTermToken())
            args.push_back(createTerm());
    return args;
}

Term *Parser::createTail()
{
    if (_token.first != ']' && _token.first != '|')
        throw string("Unexpected tail token " + _token.second + ".");

    if (_token.first == ']')
        return _termFactory->createAtom("[]");
    updateToken();
    Term *tail = createTerm();
    updateToken();
    return tail;
}

bool Parser::hasNextArg()
{
    return (_token.first == ',' || isTermToken());
}

bool Parser::isTermToken()
{
    for (int i = 0; i < _termTokens.size(); i++)
        if (_token.first == _termTokens[i])
            return true;
    return false;
}