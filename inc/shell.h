#ifndef SHELL_H
#define SHELL_H
#include "parser.h"
#include "scanner.h"
#include "expBuilder.h"

class Shell
{
public:
  Shell();
  void run();

private:
  void interpret();
  void compile();
  void reply(Exp *expTree, Parser *parser);
  void iterateClause(Iterator<Exp *> *it, Parser *parser);
  void createAnswer(vector<Variable *> variables, bool &isFirstOne);
  void output(string text, int crlf, bool isRed = false);

  bool _isHalt;
  string _query; // user query
};

#endif