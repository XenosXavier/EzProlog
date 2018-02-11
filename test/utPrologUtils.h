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
    string content = "#$&*+-./:<->?@^~\\";
    for (int i = 0; i < content.length(); i++)
        ASSERT_TRUE(prologUtils->isSpecialChar(content[i]));
}

TEST_F(PrologUtilsTest, isOperator)
{
    string content = "=,;";
    for (int i = 0; i < content.length(); i++)
        ASSERT_TRUE(prologUtils->isOperator(string(1, content[i])));
}

TEST_F(PrologUtilsTest, getOpPriority)
{
    int priority[] = {700, 1000, 1100};
    string content = "=,;";
    for (int i = 0; i < content.length(); i++)
        ASSERT_EQ(priority[i], prologUtils->getOpPriority(string(1, content[i])));
}

#endif