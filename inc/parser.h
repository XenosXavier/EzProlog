#ifndef PARSER_H
#define PARSER_H
#include "scanner.h"
#include "expBuilder.h"
#include "termFactory.h"
#include <gtest/gtest_prod.h>

/**
 * [Builder Pattern - Client]
 * The ez-prolog parser. Create the term factory for 
 * each clauses, convert the token to corresponding
 * node and then add it into expression builder.
 * Finally use buildExpTree to create an expression
 * tree for ez-prolog.
 */
class Parser
{
public:
  Parser(Scanner &scanner, ExpBuilder &expBuilder);
  void parse();
  vector<Variable *> clauseVariables(int index);

private:
  FRIEND_TEST(parser, createTerm);
  FRIEND_TEST(parser, createAtomOrCompound);
  FRIEND_TEST(parser, createParenthesesCompound);
  FRIEND_TEST(parser, missingRightParentheses);
  FRIEND_TEST(parser, createBracketsCompound);
  FRIEND_TEST(parser, missingRightBrackets);
  FRIEND_TEST(parser, createArgs);
  FRIEND_TEST(parser, createTail);
  FRIEND_TEST(parser, hasNextArg);
  FRIEND_TEST(parser, isTermToken);

  void createTermFactory();
  void updateToken();
  Term *createTerm();
  Term *createAtomOrCompound();
  Term *createParenthesesCompound(Atom *functor);
  Term *createBracketsCompound();
  vector<Term *> createArgs();
  Term *createTail();
  bool hasNextArg();
  bool isTermToken();
  bool isEndOfQuery();
  bool isLegalQuery();

  Scanner &_scanner;
  ExpBuilder &_expBuilder;
  PrologUtils *_prologUtils;
  TermFactory *_termFactory;
  vector<TermFactory *> _termFactories;
  pair<int, string> _token;
  vector<int> _termTokens;
};

#endif