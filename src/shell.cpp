#include "../inc/shell.h"
#include "../inc/iterator.h"
#include <iostream>

Shell::Shell() : _isHalt(false), _query("")
{
}

void Shell::run()
{
    string buffer;
    while (!_isHalt)
    {
        output((_query.empty()) ? "?-" : "| ", 0);
        std::getline(std::cin, buffer);
        _query += buffer;
        if (_query.back() == '.')
            interpret();
    }
}

void Shell::interpret()
{
    if (_query == "halt.")
        _isHalt = true;
    else
        compile();
    _query = "";
}

void Shell::compile()
{
    Scanner scanner(_query);
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    try
    {
        parser.parse();
        reply(expBuilder.getExpTree(), &parser);
    }
    catch (const std::string &exception)
    {
        output(exception, 2, true);
    }
    catch (...)
    {
        output("Unexpceted exception", 2, true);
    }
}

void Shell::reply(Exp *expTree, Parser *parser)
{
    if (expTree->evaluate())
        iterateClause(expTree->createRightRecursiveIterator(), parser);
    else
        output("false.", 2, true);
}

void Shell::iterateClause(Iterator<Exp *> *it, Parser *parser)
{
    int i = 0;
    bool isFirstOne = true;
    for (it->first(); !it->isDone(); it->next(), i++)
        if (it->currentItem()->evaluate())
            createAnswer(parser->clauseVariables(i), isFirstOne);
    if (i == 0)
        createAnswer(parser->clauseVariables(i), isFirstOne);
    output(".", 2);
}

void Shell::createAnswer(vector<Variable *> variables, bool &isFirstOne)
{
    if (isFirstOne)
        isFirstOne = false;
    else
        output(";", 1);

    for (int i = 0; i < variables.size(); i++)
    {
        output((i > 0) ? "," : "", (i > 0));
        output(variables[i]->symbol() + " = " + variables[i]->value(), 0);
    }
    if (variables.empty())
        output("true", 0);
}

void Shell::output(string text, int crlf, bool isRed)
{

    if (isRed)
        std::cout << "\033[1;31m" << text << "\033[0m";
    else
        std::cout << text;
    for (int i = 0; i < crlf; i++)
        std::cout << std::endl;
}