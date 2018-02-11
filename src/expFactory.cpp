#include "../inc/expFactory.h"

// Creates a matching expression.
MatchingExp *ExpFactory::createMatchingExp(Term *left, Term *right)
{
    if (left == nullptr || right == nullptr)
        throw string("Uncompleted matching expression");
    return new MatchingExp(left, right);
}

// Creates an and(conjunction) expression.
AndExp *ExpFactory::createAndExp(Exp *left, Exp *right)
{
    if (left == nullptr || right == nullptr)
        throw string("Uncompleted conjunction expression");
    return new AndExp(left, right);
}

// Creates an or(disjunction) expression.
OrExp *ExpFactory::createOrExp(Exp *left, Exp *right)
{
    if (left == nullptr || right == nullptr)
        throw string("Uncompleted disjunction expression");
    return new OrExp(left, right);
}