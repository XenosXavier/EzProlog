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
  FRIEND_TEST(Parser, createTerm);
  FRIEND_TEST(Parser, createAtomOrStructure);
  FRIEND_TEST(Parser, createStructure);
  FRIEND_TEST(Parser, missingRightParenthesis);
  FRIEND_TEST(Parser, createList);
  FRIEND_TEST(Parser, missingRightBrackets);
  FRIEND_TEST(Parser, createArgs);
  FRIEND_TEST(Parser, createTail);
  FRIEND_TEST(Parser, hasNextArg);
  FRIEND_TEST(Parser, isTermToken);

  void createTermFactory();
  void updateToken();
  Term *createTerm();
  Term *createAtomOrStructure();
  Term *createStructure(Atom *functor);
  Term *createList();
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