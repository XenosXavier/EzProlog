#ifndef SHELL_H
#define SHELL_H
#include "parser.h"
#include "scanner.h"
#include "expBuilder.h"

/**
 * The ez-prolog shell.
 * Provide a console interface for user
 * to input query and get the response
 * from ez-prolog.
 */
class Shell
{
public:
  Shell();
  void run();

private:
  void interpret();
  void compile();
  void reply(Exp *expTree, Parser *parser);
  void showResult(Iterator<Exp *> *it, Parser *parser);
  string getClauseAnswer(vector<Variable *> variables);
  string getEquivalent(Variable *variable);
  string convertToBrackets(Structure *compound);
  bool isBracketsCompound(Structure *compound);
  void output(string text, bool isRed = false);

  bool _isHalt;
  string _query;
};

#endif