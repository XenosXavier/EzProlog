#include "../inc/shell.h"
#include "../inc/iterator.h"
#include <iostream>

Shell::Shell() : _isHalt(false), _query("")
{
}

// Run the shell.
void Shell::run()
{
    string buffer;
    while (!_isHalt)
    {
        output((_query.empty()) ? "?-" : "| ");
        std::getline(std::cin, buffer);
        _query += buffer;
        if (_query.back() == '.') // Interpret the query if last char is '.'.
            interpret();
    }
}

// Interpret the query.
void Shell::interpret()
{
    if (_query == "halt.") // Exit the ez-prolog if query is halt.
        _isHalt = true;
    else
        compile();
    _query = ""; // Clear the query.
}

// Complie the query.
void Shell::compile()
{
    Scanner scanner(_query);
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    try // Try to parse user query and show the result.
    {
        parser.parse();
        reply(expBuilder.getExpTree(), &parser);
    }
    catch (const std::string &exception) // Catch any string exception.
    {
        output(exception + "\n\n", true);
    }
    catch (...) // Catch all type exception.
    {
        output("Unexpected error\n\n", true);
    }
}

// Reply the result of user query.
void Shell::reply(Exp *expTree, Parser *parser)
{
    if (expTree->evaluate()) // Show result if query is true.
        showResult(expTree->createClauseIterator(), parser);
    else // Otherwise display 'false' on console.
        output("false.\n\n", true);
}

// Show all clause results of user query.
void Shell::showResult(Iterator<Exp *> *it, Parser *parser)
{
    string result = "";
    int i = 0;
    // Iterate all clauses.
    for (it->first(); !it->isDone(); it->next(), i++)
        if (it->currentItem()->evaluate()) // Show result if clause is true.
            result += ((result.empty()) ? "" : ";\n") + getClauseAnswer(parser->clauseVariables(i));
    if (i == 0) // Show result if there is only one clause.
        result += getClauseAnswer(parser->clauseVariables(i));
    output(result + ".\n\n");
}

// Show all variables value of this clause.
string Shell::getClauseAnswer(vector<Variable *> variables)
{
    string answer = "";
    for (int i = 0, count = variables.size(); i < count; i++)
        if (variables[i]->instance() != nullptr)
            answer += ((answer.empty()) ? "" : ",\n") + getEquivalent(variables[i]);
    if (answer.empty()) // Display 'true' if the answer string is empty.
        answer = "true";
    return answer;
}

// Get the equivalent of this variable.
string Shell::getEquivalent(Variable *variable)
{
    string equivalent = variable->symbol() + " = ";
    Term *instance = variable->instance();
    Structure *compound = instance->getStructure();

    // Convert structure to brackets compound output.
    if (compound != nullptr && isBracketsCompound(compound))
        equivalent += convertToBrackets(compound);
    // Show the symbol if instance is another variable.
    else if (instance->getVariable() != nullptr)
        equivalent += instance->symbol();
    // Otherwise show the value of instance.
    else
        equivalent += variable->value();
    return equivalent;
}

// Convert the structure to brackets output.
// Example: (1) .(a, .(b, [])) -> [a, b]
//          (2) .(a, b) -> [a|b]
string Shell::convertToBrackets(Structure *compound)
{
    string bracketsOutput = "[";
    Structure *root = compound;
    Term *tail;
    for (; compound != nullptr; compound = tail->getStructure())
    {
        bracketsOutput += ((root == compound) ? "" : ", ") + compound->arg(0)->value();
        tail = compound->arg(1);
        if (tail->getStructure() == nullptr && tail->symbol() != "[]")
            bracketsOutput += "|" + tail->value();
    }
    return bracketsOutput + "]";
}

// Returns ture if this structure is a brackets compound.
bool Shell::isBracketsCompound(Structure *compound)
{
    return (compound->functor()->symbol() == "." && compound->arity() == 2);
}

// Show result on console.
void Shell::output(string text, bool isRed)
{
    if (isRed)
        std::cout << "\033[1;31m" << text << "\033[0m";
    else
        std::cout << text;
}