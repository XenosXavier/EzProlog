#ifndef SCANNER_H
#define SCANNER_H
#include "prologUtils.h"
#include <string>
#include <utility>
#include <gtest/gtest_prod.h>
using std::pair;
using std::string;

/**
 * The ez-prolog scanner.
 * Extract a simple object token each time
 * in nextToken. Provide client to peek the
 * current, next character and now position
 * of this content.
 */
class Scanner
{
public:
  Scanner(string content = "");
  pair<int, string> nextToken();
  int position();
  char currentChar();
  char nextChar();

private:
  FRIEND_TEST(ScannerTest, skipLeadingWhiteSpace);
  FRIEND_TEST(ScannerTest, extractAtom);
  FRIEND_TEST(ScannerTest, extractAtomSC);
  FRIEND_TEST(ScannerTest, extractAtomSQ);
  FRIEND_TEST(ScannerTest, extractNumber);
  FRIEND_TEST(ScannerTest, extractVariable);
  FRIEND_TEST(ScannerTest, extractChar);
  FRIEND_TEST(ScannerTest, position);
  FRIEND_TEST(ScannerTest, currentChar);
  FRIEND_TEST(ScannerTest, nextChar);
  FRIEND_TEST(ScannerTest, isNumberChar);
  FRIEND_TEST(ScannerTest, isEndChar);

  int skipLeadingWhiteSpace();
  pair<int, string> extractAtom();
  pair<int, string> extractAtomSC();
  pair<int, string> extractAtomSQ();
  pair<int, string> extractNumber();
  pair<int, string> extractVariable();
  pair<int, string> extractChar();
  bool isNumberChar(bool &hasPoint);
  bool isEndChar();

  string _content;
  int _position;
  PrologUtils *_prologUtils;
};

#endif