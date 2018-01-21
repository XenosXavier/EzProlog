#include "../inc/expFactory.h"

MatchingExp *ExpFactory::createMatchingExp(Term *left, Term *right)
{
    if (left == nullptr)
        throw string("Missing term before '='.");
    if (right == nullptr)
        throw string("Missing term after '='.");
    return new MatchingExp(left, right);
}

AndExp *ExpFactory::createAndExp(Exp *left, Exp *right)
{
    if (left == nullptr)
        throw string("Missing expression before ','.");
    if (right == nullptr)
        throw string("Missing expression after ','.");
    return new AndExp(left, right);
}

OrExp *ExpFactory::createOrExp(Exp *left, Exp *right)
{
    if (left == nullptr)
        throw string("Missing expression before ';'.");
    if (right == nullptr)
        throw string("Missing expression after ';'.");
    return new OrExp(left, right);
}