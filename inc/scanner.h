#ifndef SCANNER_H
#define SCANNER_H
#include "prologUtils.h"
#include <string>
#include <utility>
#include <gtest/gtest_prod.h>
using std::pair;
using std::string;

class Scanner
{
public:
  Scanner(string context = "");
  pair<int, string> nextToken();
  int skipLeadingWhiteSpace();
  pair<int, string> extractAtom();
  pair<int, string> extractAtomSC();
  pair<int, string> extractAtomSQ();
  pair<int, string> extractNumber();
  pair<int, string> extractVariable();
  pair<int, string> extractChar();
  int position();
  char currentChar();
  char nextChar();

private:
  FRIEND_TEST(ScannerTest, isNumberChar);
  FRIEND_TEST(ScannerTest, isEndChar);

  bool isNumberChar(bool &hasPoint);
  bool isEndChar();
  string _context;
  int _position;
  PrologUtils *_prologUtils;
};

#endif