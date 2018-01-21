#ifndef UT_PROLOG_UTILS_H
#define UT_PROLOG_UTILS_H
#include "../inc/prologUtils.h"

class PrologUtilsTest : public ::testing::Test
{
  public:
    PrologUtils *prologUtils;

  protected:
    void SetUp()
    {
        prologUtils = PrologUtils::getInstance();
    }
};

TEST_F(PrologUtilsTest, isSpecialChar)
{
    string context = "#$&*+-./:<->?@^~\\";
    for (int i = 0; i < context.length(); i++)
        ASSERT_TRUE(prologUtils->isSpecialChar(context[i]));
}

TEST_F(PrologUtilsTest, isOperator)
{
    string context = "=,;";
    for (int i = 0; i < context.length(); i++)
        ASSERT_TRUE(prologUtils->isOperator(string(1, context[i])));
}

TEST_F(PrologUtilsTest, getOpPriority)
{
    int priority[] = {700, 1000, 1100};
    string context = "=,;";
    for (int i = 0; i < context.length(); i++)
        ASSERT_EQ(priority[i], prologUtils->getOpPriority(string(1, context[i])));
}

#endif