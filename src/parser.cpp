#include "../inc/parser.h"
#include <algorithm>
#include <iostream>

Parser::Parser(Scanner &scanner, ExpBuilder &expBuilder) : _scanner(scanner), _expBuilder(expBuilder), _prologUtils(PrologUtils::getInstance())
{
    _termTokens = {_prologUtils->ATOM, _prologUtils->NUMBER, _prologUtils->VAR, '['};
    createTermFactory();
}

// Parse the token from scanner and add it into
// expression builder with corresponding node.
// Build the expression tree after all nodes has
// been added into expression builder.
void Parser::parse()
{
    for (updateToken(); !isEndOfQuery(); updateToken())
    {
        if (isTermToken()) // Create term if this token is a term token.
            _expBuilder.addTermNode(createTerm());
        else if (_prologUtils->isOperator(_token.second)) // Otherwise it must be operator.
        {
            if (_token.first == ';') // If this token is disjunction operator.
                createTermFactory(); // Create another term factory for new clause.
            _expBuilder.addOperatorNode(_token.second);
        }
        else // Throw exception if this token is neither term nor operator.
            throw string("Undefined token " + _token.second + ".");
    }
    if (isLegalQuery()) // Build expression if query is legal.
        _expBuilder.buildExpTree();
}

// Get all veriables of target clause.
vector<Variable *> Parser::clauseVariables(int index)
{
    if (index >= _termFactories.size()) // Throw exception if index is out of range.
        throw string("The index is out of clause size");
    map<string, Variable *> variableTable = _termFactories[index]->variableTable();
    vector<Variable *> variables;
    // Transform map<string, Variable*> to vector<Variable*>.
    std::transform(variableTable.begin(), variableTable.end(), std::back_inserter(variables), [](pair<string, Variable *> const &pair) {
        return pair.second;
    });
    // Sort the variables by those address.
    std::sort(variables.begin(), variables.end(), [](Variable *a, Variable *b) {
        return a->age() < b->age();
    });
    return variables;
}

// Create a new term factory.
void Parser::createTermFactory()
{
    _termFactory = new TermFactory();
    _termFactories.push_back(_termFactory);
}

// Get the next token from scanner.
void Parser::updateToken()
{
    _token = _scanner.nextToken();
}

// Create the corresponding term from token.
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

// Create an atom or compound(structure) if getting an atom token.
Term *Parser::createAtomOrCompound()
{
    Atom *atom = _termFactory->createAtom(_token.second);
    if (_scanner.currentChar() == '(')
        return createParenthesesCompound(atom);
    return atom;
}

// Create the parentheses compound(structure).
// Parentheses compound: functor(arg0, arg1, ..., argn).
Term *Parser::createParenthesesCompound(Atom *functor)
{
    updateToken();                      // Move to left parentheses.
    vector<Term *> args = createArgs(); // Create the compound arguments.
    if (_token.first == ')')            // Create structure if last token is ')'.
        return _termFactory->createStructure(functor, args);
    // Throw exception if the token is not ')'.
    throw string("Unexpected " + _token.second + " before ')'.");
}

// Create the brackets compound(list or structure).
// Brackets compound: .(head, tail) = [head|tail]
// Example: (1) [a, b] = .(a, .(b, [])) <- tail recursion structure
//          (2) [a|b]  = .(a, b)
Term *Parser::createBracketsCompound()
{
    vector<Term *> args = createArgs();
    Term *tail = createTail(); // Create the tail term.
    if (_token.first == ']')
    {
        Atom *functor = _termFactory->createAtom("."); // Create dot functor.
        for (int i = args.size() - 1; i >= 0; i--)     // Create tail recursion strcture.
            tail = _termFactory->createStructure(functor, {args[i], tail});
        return tail;
    }
    throw string("Unexpected " + _token.second + " before ']'.");
}

// Create compound arugments.
vector<Term *> Parser::createArgs()
{
    vector<Term *> args;
    // First update to ignore left parentheses or brackets.
    for (updateToken(); hasNextArg(); updateToken())
        if (isTermToken())
            args.push_back(createTerm());
    return args;
}

// Create brackets compound tail.
Term *Parser::createTail()
{
    if (_token.first != ']' && _token.first != '|')
        throw string("Unexpected tail token " + _token.second + "of compound.");

    if (_token.first == ']') // Return empty list '[]' if token is ']'.
        return _termFactory->createAtom("[]");
    updateToken();             // Ignore '|' token.
    Term *tail = createTerm(); // Create tail term.
    updateToken();             // Move to the end of compound.
    return tail;
}

// Returns true if there is any argument.
bool Parser::hasNextArg()
{
    return (_token.first == ',' || isTermToken());
}

// Returns true if termTokens contain this token.
bool Parser::isTermToken()
{
    for (int i = 0; i < _termTokens.size(); i++)
        if (_token.first == _termTokens[i])
            return true;
    return false;
}

// Returns true if current token is the end of query.
bool Parser::isEndOfQuery()
{
    return (_token.first == '.' || _token.first == _prologUtils->EOS);
}

// Check if query is legal or not.
bool Parser::isLegalQuery()
{
    if (_token.first != '.') // Throw exception if the last char is not '.'.
        throw string("Missing token '.' at the end of clause.");
    else if (_scanner.nextChar() != '\0') // Throw exception if char is not the last one.
        throw string("Token '.' is not the end of clause");
    return true;
}