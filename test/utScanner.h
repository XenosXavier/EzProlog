#ifndef UT_SCANNER_H
#define UT_SCANNER_H
#include "../inc/scanner.h"

class ScannerTest : public ::testing::Test
{
  public:
    PrologUtils *prologUtils;
    pair<int, string> token;

  protected:
    void SetUp()
    {
        prologUtils = PrologUtils::getInstance();
    }
};

TEST_F(ScannerTest, extractAtom)
{
    Scanner scanner("lower");
    token = scanner.extractAtom();
    ASSERT_EQ(prologUtils->ATOM, token.first);
    ASSERT_EQ("lower", token.second);
}

TEST_F(ScannerTest, extractAtomSC)
{
    Scanner scanner("#$&*+-./:<->?@^~\\");
    token = scanner.extractAtomSC();
    ASSERT_EQ(prologUtils->ATOM, token.first);
    ASSERT_EQ("#$&*+-./:<->?@^~\\", token.second);
}

TEST_F(ScannerTest, extractAtomSQ)
{
    Scanner scanner("'This is a atom token'");
    token = scanner.extractAtomSQ();
    ASSERT_EQ(prologUtils->ATOM, token.first);
    ASSERT_EQ("'This is a atom token'", token.second);
}

TEST_F(ScannerTest, extractNumber)
{
    Scanner scanner("0.123");
    token = scanner.extractNumber();
    ASSERT_EQ(prologUtils->NUMBER, token.first);
    ASSERT_EQ("0.123", token.second);
}

TEST_F(ScannerTest, extractVariable)
{
    Scanner scanner("_scroll");
    token = scanner.extractVariable();
    ASSERT_EQ(prologUtils->VAR, token.first);
    ASSERT_EQ("_scroll", token.second);
}

TEST_F(ScannerTest, extractChar)
{
    Scanner scanner("(");
    token = scanner.extractChar();
    ASSERT_EQ('(', token.first);
    ASSERT_EQ("(", token.second);
}

TEST_F(ScannerTest, skipLeadingWhiteSpace)
{
    // --------------012345678
    Scanner scanner("   hello");
    ASSERT_EQ(3, scanner.skipLeadingWhiteSpace());
}

TEST_F(ScannerTest, position)
{
    // --------------012345678
    Scanner scanner("   hello");
    ASSERT_EQ(0, scanner.position());
    scanner.skipLeadingWhiteSpace();
    ASSERT_EQ(3, scanner.position());
    scanner.nextToken();
    ASSERT_EQ(8, scanner.position());
}

TEST_F(ScannerTest, currentChar)
{
    Scanner scanner("var");
    ASSERT_EQ('v', scanner.currentChar());
    scanner.extractChar();
    ASSERT_EQ('a', scanner.currentChar());
    scanner.extractChar();
    ASSERT_EQ('r', scanner.currentChar());
    scanner.extractChar();
    ASSERT_EQ('\0', scanner.currentChar());
}

TEST_F(ScannerTest, nextChar)
{
    Scanner scanner("ab");
    ASSERT_EQ('b', scanner.nextChar());
    scanner.extractChar();
    ASSERT_EQ('\0', scanner.nextChar());
    scanner.extractChar();
    ASSERT_EQ('\0', scanner.nextChar());
}

TEST_F(ScannerTest, isCharacter)
{
    Scanner scanner("a1_$");
    ASSERT_TRUE(scanner.isCharacter());
    scanner.extractChar();
    ASSERT_TRUE(scanner.isCharacter());
    scanner.extractChar();
    ASSERT_TRUE(scanner.isCharacter());
    scanner.extractChar();
    ASSERT_FALSE(scanner.isCharacter());
}

TEST_F(ScannerTest, isNumber)
{
    Scanner scanner("1. 1.1.1");
    bool hasPoint = false;
    ASSERT_TRUE(scanner.isNumber(hasPoint));
    scanner.extractChar();
    ASSERT_FALSE(scanner.isNumber(hasPoint));
    scanner.extractChar();
    scanner.skipLeadingWhiteSpace();

    hasPoint = false;
    ASSERT_TRUE(scanner.isNumber(hasPoint));
    scanner.extractChar();
    ASSERT_TRUE(scanner.isNumber(hasPoint));
    scanner.extractChar();
    ASSERT_TRUE(scanner.isNumber(hasPoint));
    scanner.extractChar();
    ASSERT_FALSE(scanner.isNumber(hasPoint));
    scanner.extractChar();
}

TEST_F(ScannerTest, isEndChar)
{
    Scanner scanner("..");
    ASSERT_FALSE(scanner.isEndChar());
    scanner.extractChar();
    ASSERT_TRUE(scanner.isEndChar());
}

TEST_F(ScannerTest, nextToken)
{
    Scanner scanner("a . 'a b' X _ 0.1 2.");
    token = scanner.nextToken();
    ASSERT_EQ(prologUtils->ATOM, token.first);
    ASSERT_EQ("a", token.second);
    token = scanner.nextToken();
    ASSERT_EQ(prologUtils->ATOM, token.first);
    ASSERT_EQ(".", token.second);
    token = scanner.nextToken();
    ASSERT_EQ(prologUtils->ATOM, token.first);
    ASSERT_EQ("'a b'", token.second);
    token = scanner.nextToken();
    ASSERT_EQ(prologUtils->VAR, token.first);
    ASSERT_EQ("X", token.second);
    token = scanner.nextToken();
    ASSERT_EQ(prologUtils->VAR, token.first);
    ASSERT_EQ("_", token.second);
    token = scanner.nextToken();
    ASSERT_EQ(prologUtils->NUMBER, token.first);
    ASSERT_EQ("0.1", token.second);
    token = scanner.nextToken();
    ASSERT_EQ(prologUtils->NUMBER, token.first);
    ASSERT_EQ("2", token.second);
    token = scanner.nextToken();
    ASSERT_EQ('.', token.first);
    ASSERT_EQ(".", token.second);
}

#endif