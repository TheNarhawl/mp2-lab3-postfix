#include "../base/postfix.h"
#include <gtest.h>

using VALUES = std::map<char, double>;

TEST(Postfix, can_create_postfix)
{
    ASSERT_NO_THROW(Postfix p("a+b"));
}

TEST(Postfix, postfix_simple_is_correct)
{
    Postfix p("a+b");
    ASSERT_EQ(p.getPostfix(), "ab+");
}

TEST(Postfix, postfix_with_brackets_is_correct)
{
    Postfix p("c*(a+b)");
    ASSERT_EQ(p.getPostfix(), "cab+*");
}

TEST(Postfix, can_calculate_simple)
{
    Postfix p("a+b");
    VALUES v = {{'a', 5}, {'b', 6}};
    ASSERT_EQ(p.calculate(v), 11);
}

TEST(Postfix, can_calculate_with_brackets)
{
    Postfix p("c*(a+b)");
    VALUES v = {{'a', 1}, {'b', 4}, {'c', 2}};
    ASSERT_EQ(p.calculate(v), 10);
}

TEST(Postfix, throws_exception_with_wrong_brackets)
{
    EXPECT_ANY_THROW(Postfix p("(a+b(*)c"));
}   

TEST(Postfix, throws_exception_with_wrong_brackets2)
{
    EXPECT_ANY_THROW(Postfix p("(c*(a+b)"));
}

TEST(Postfix, can_get_infix)
{
    Postfix p("c*(a+b)");
    ASSERT_EQ(p.getInfix(), "c*(a+b)");
}