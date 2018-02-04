#ifndef PROLOG_UTILS
#define PROLOG_UTILS
#include <map>
#include <string>
using std::map;
using std::string;

/**
 * [Singleton Pattern]
 * The ez-prolog utility.
 * Provide some utility method and const.
 */
class PrologUtils
{
public:
  static PrologUtils *getInstance();
  bool isSpecialChar(char c);
  bool isOperator(string op);
  int getOpPriority(string op);
  const int EOS = '\0';
  const int ATOM = 256;
  const int NUMBER = 257;
  const int VAR = 258;

protected:
  PrologUtils();

private:
  map<string, int> _opPriorityTable;
  static PrologUtils *_instance;
};

#endif