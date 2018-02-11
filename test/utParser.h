#ifndef UT_PARSER_H
#define UT_PARSER_H
#include "../inc/parser.h"

TEST(Parser, createTerm)
{
    Scanner scanner("a 0.1 X s() s(a, b) [] [a, b] [a|b]");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.updateToken();
    ASSERT_EQ("a", parser.createTerm()->symbol());
    parser.updateToken();
    ASSERT_EQ("0.1", parser.createTerm()->symbol());
    parser.updateToken();
    ASSERT_EQ("X", parser.createTerm()->symbol());
    parser.updateToken();
    ASSERT_EQ("s()", parser.createTerm()->symbol());
    parser.updateToken();
    ASSERT_EQ("s(a, b)", parser.createTerm()->symbol());
    parser.updateToken();
    ASSERT_EQ("[]", parser.createTerm()->symbol());
    parser.updateToken();
    ASSERT_EQ(".(a, .(b, []))", parser.createTerm()->symbol());
    parser.updateToken();
    ASSERT_EQ(".(a, b)", parser.createTerm()->symbol());
}

TEST(Parser, createAtomOrCompound)
{
    Scanner scanner("a f(a, b)");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.updateToken();
    ASSERT_EQ("a", parser.createAtomOrCompound()->symbol());
    parser.updateToken();
    ASSERT_EQ("f(a, b)", parser.createAtomOrCompound()->symbol());
}

TEST(Parser, createParenthesesCompound)
{
    Scanner scanner("(a, b)");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    ASSERT_EQ("s(a, b)", parser.createParenthesesCompound(new Atom("s"))->symbol());
}

TEST(Parser, missingRightParentheses)
{
    Scanner scanner("(a, b");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    try
    {
        parser.createParenthesesCompound(new Atom("s"));
        FAIL() << "It should throw 'Unexpected  before ')'.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Unexpected  before ')'.", exception);
    }
}

TEST(Parser, createBracketsCompound)
{
    Scanner scanner("[a, b]");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.updateToken();
    ASSERT_EQ(".(a, .(b, []))", parser.createBracketsCompound()->symbol());
}

TEST(Parser, missingRightBrackets)
{
    Scanner scanner("[a, b");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    try
    {
        parser.createBracketsCompound();
        FAIL() << "It should throw 'Unexpected tail token of compound.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Unexpected tail token of compound.", exception);
    }
}

TEST(Parser, createArgs)
{
    Scanner scanner("a, 0.1, X, s(), [], s(a, b), [a, b]");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    vector<Term *> args = parser.createArgs();
    ASSERT_EQ(7, args.size());
    ASSERT_EQ("a", args[0]->symbol());
    ASSERT_EQ("0.1", args[1]->symbol());
    ASSERT_EQ("X", args[2]->symbol());
    ASSERT_EQ("s()", args[3]->symbol());
    ASSERT_EQ("[]", args[4]->symbol());
    ASSERT_EQ("s(a, b)", args[5]->symbol());
    ASSERT_EQ(".(a, .(b, []))", args[6]->symbol());
}

TEST(Parser, createTail)
{
    Scanner scanner("]|b");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.updateToken();
    ASSERT_EQ("[]", parser.createTail()->symbol());
    parser.updateToken();
    ASSERT_EQ("b", parser.createTail()->symbol());

    try
    {
        parser.createTail();
        FAIL() << "It should throw 'Unexpected tail token of compound.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Unexpected tail token of compound.", exception);
    }
}

TEST(Parser, hasNextArg)
{
    Scanner scanner("a)]|");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.updateToken();
    ASSERT_TRUE(parser.hasNextArg());
    parser.updateToken();
    ASSERT_FALSE(parser.hasNextArg());
    parser.updateToken();
    ASSERT_FALSE(parser.hasNextArg());
    parser.updateToken();
    ASSERT_FALSE(parser.hasNextArg());
    parser.updateToken();
    ASSERT_FALSE(parser.hasNextArg());
}

TEST(Parser, isTermToken)
{
    Scanner scanner("a 1 X [ .");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.updateToken();
    ASSERT_TRUE(parser.isTermToken());
    parser.updateToken();
    ASSERT_TRUE(parser.isTermToken());
    parser.updateToken();
    ASSERT_TRUE(parser.isTermToken());
    parser.updateToken();
    ASSERT_TRUE(parser.isTermToken());
    parser.updateToken();
    ASSERT_FALSE(parser.isTermToken());
}

TEST(Parser, parseMatchingExp)
{
    Scanner scanner("X=tom.");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.parse();
    Exp *root = expBuilder.getExpTree();
    ASSERT_TRUE(root->evaluate());
}

TEST(Parser, parseAndExp)
{
    Scanner scanner("X=tom, X=1.");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.parse();
    Exp *root = expBuilder.getExpTree();
    ASSERT_FALSE(root->evaluate());
}

TEST(Parser, parseOrExp)
{
    Scanner scanner("X=tom; X=1.");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    parser.parse();
    Exp *root = expBuilder.getExpTree();
    ASSERT_TRUE(root->evaluate());
}

TEST(Parser, missDot)
{
    Scanner scanner("X=tom");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    try
    {
        parser.parse();
        FAIL() << "It should throw 'Missing token '.' at the end of clause.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Missing token '.' at the end of clause.", exception);
    }
}

TEST(Parser, undefineToken)
{
    Scanner scanner("}.");
    ExpBuilder expBuilder;
    Parser parser(scanner, expBuilder);
    try
    {
        parser.parse();
        FAIL() << "It should throw 'Undefined token }.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Undefined token }.", exception);
    }
}

#endif