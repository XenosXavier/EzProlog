#include "../inc/expFactory.h"

// Creates a matching expression.
MatchingExp *ExpFactory::createMatchingExp(Term *left, Term *right)
{
    if (left == nullptr || right == nullptr)
        throw string("Missing a term of operator '='");
    return new MatchingExp(left, right);
}

// Creates an and(conjunction) expression.
AndExp *ExpFactory::createAndExp(Exp *left, Exp *right)
{
    if (left == nullptr || right == nullptr)
        throw string("Missing an expression of operator ','");
    return new AndExp(left, right);
}

// Creates an or(disjunction) expression.
OrExp *ExpFactory::createOrExp(Exp *left, Exp *right)
{
    if (left == nullptr || right == nullptr)
        throw string("Missing an expression of operator ';'");
    return new OrExp(left, right);
}