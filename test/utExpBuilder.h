#ifndef UT_EXP_BUILDER_H
#define UT_EXP_BUILDER_H
#include "../inc/expBuilder.h"
#include "../inc/atom.h"

TEST(ExpBuilder, addTermNode)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    ASSERT_EQ("tom", expBuilder._termNodes.top()->symbol());
    expBuilder.addTermNode(new Atom("jerry"));
    ASSERT_EQ("jerry", expBuilder._termNodes.top()->symbol());
}

TEST(ExpBuilder, addOperatorNode)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    ASSERT_EQ("=", expBuilder._opNodes.top());
    expBuilder.addTermNode(new Atom("jerry"));
    expBuilder.addOperatorNode(",");
    ASSERT_EQ(",", expBuilder._opNodes.top());
    ASSERT_EQ(0, expBuilder._termNodes.size());
    ASSERT_EQ(1, expBuilder._expTrees.size());
}

TEST(ExpBuilder, buildExpTree)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("jerry"));
    expBuilder.buildExpTree();
    ASSERT_EQ(0, expBuilder._termNodes.size());
    ASSERT_EQ(0, expBuilder._opNodes.size());
    ASSERT_EQ(1, expBuilder._expTrees.size());
}

TEST(ExpBuilder, getExpTree)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("jerry"));
    ASSERT_THROW(expBuilder.getExpTree(), std::string);
    try
    {
        expBuilder.getExpTree();
        FAIL() << "It should throw 'Unexpected end of clause.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Unexpected end of clause.", exception);
    }
    expBuilder.buildExpTree();
    ASSERT_TRUE(expBuilder.getExpTree());
    ASSERT_FALSE(expBuilder.getExpTree()->evaluate());
}

// tom = jerry
TEST(ExpBuilder, createMatchingExpression)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("jerry"));
    expBuilder.createExpression();
    ASSERT_TRUE(expBuilder.getExpTree());
    ASSERT_FALSE(expBuilder.getExpTree()->evaluate());
}

// tom = jerry, anne = anne
TEST(ExpBuilder, createAndExpression)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("jerry"));
    expBuilder.addOperatorNode(",");
    expBuilder.addTermNode(new Atom("anne"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("anne"));
    expBuilder.createExpression(); // create anne = anne
    expBuilder.createExpression(); // create and expression
    ASSERT_TRUE(expBuilder.getExpTree());
    ASSERT_FALSE(expBuilder.getExpTree()->evaluate());
}

// tom = jerry; anne = anne
TEST(ExpBuilder, createOrExpression)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("jerry"));
    expBuilder.addOperatorNode(";");
    expBuilder.addTermNode(new Atom("anne"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("anne"));
    expBuilder.createExpression(); // create anne = anne
    expBuilder.createExpression(); // create or expression
    ASSERT_TRUE(expBuilder.getExpTree());
    ASSERT_TRUE(expBuilder.getExpTree()->evaluate());
}

/* There are two term nodes, tom and jerry, in the term stack
 * and also an operator node '=' in the operator stack. In the
 * following test, try to create expression when getting the
 * lower priority of new operator */
TEST(ExpBuilder, tryToCreateExpression)
{
    ExpBuilder expBuilder;
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("jerry"));

    // the new op priority is not greater than the top op of stack //
    expBuilder.tryToCreateExpression("=");
    ASSERT_THROW(expBuilder.getExpTree(), std::string);
    try
    {
        expBuilder.getExpTree();
        FAIL() << "It should throw 'Unexpected end of clause.'";
    }
    catch (const std::string &exception)
    {
        ASSERT_EQ("Unexpected end of clause.", exception);
    }

    // the new op priority is greater than the top of of stack
    expBuilder.tryToCreateExpression(",");
    ASSERT_TRUE(expBuilder.getExpTree());
    ASSERT_FALSE(expBuilder.getExpTree()->evaluate());
}

TEST(ExpBuilder, stackException)
{
    ExpBuilder expBuilder;
    // It should return the default value of T when stack is empty
    ASSERT_EQ("", expBuilder.extractLast(expBuilder._opNodes));
    ASSERT_EQ(nullptr, expBuilder.extractLast(expBuilder._termNodes));
    ASSERT_EQ(nullptr, expBuilder.extractLast(expBuilder._expTrees));
    // It should return the top value when stack is not empty
    expBuilder.addTermNode(new Atom("tom"));
    ASSERT_EQ("tom", expBuilder.extractLast(expBuilder._termNodes)->symbol());
    expBuilder.addOperatorNode("=");
    ASSERT_EQ("=", expBuilder.extractLast(expBuilder._opNodes));
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.addOperatorNode("=");
    expBuilder.addTermNode(new Atom("tom"));
    expBuilder.buildExpTree();
    ASSERT_TRUE(expBuilder.extractLast(expBuilder._expTrees)->evaluate());
}

#endif