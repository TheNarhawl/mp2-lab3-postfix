#include "../base/TStack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> stack(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack<int> stack(-5));
}

TEST(TStack, can_push_element)
{
    TStack<int> stack(1);
    stack.push(123);

    ASSERT_EQ(123, stack.back());
}

TEST(TStack, operator_equal_true_when_stacks_are_equal)
{
    TStack<int> stack1(5);
    stack1.push(123);
    stack1.push(999);
    stack1.push(100);

    TStack<int> stack2(5);
    stack2.push(123);
    stack2.push(999);
    stack2.push(100);

    ASSERT_TRUE(stack1 == stack2);
}

TEST(TStack, operator_equal_false_when_stacks_are_not_equal)
{
    TStack<int> stack1(5);
    stack1.push(123);
    stack1.push(999);
    stack1.push(100);

    TStack<int> stack2(5);
    stack2.push(123);
    stack2.push(999);
    stack2.push(999);

    ASSERT_FALSE(stack1 == stack2);
}

TEST(TStack, operator_equal_false_when_stacks_are_diff_size)
{
    TStack<int> stack1(5);
    stack1.push(123);
    stack1.push(999);
    stack1.push(100);

    TStack<int> stack2(5);
    stack2.push(123);
    stack2.push(999);
    stack1.push(100);
    stack1.push(100);

    ASSERT_FALSE(stack1 == stack2);
}

TEST(TStack, can_copy_from_vector)
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    TStack<int> stack(vec);
    TStack<int> controlStack(vec.size());
    std::for_each(vec.begin(), vec.end(), [&controlStack](int element)
    {
        controlStack.push(element);
    });

    ASSERT_EQ(stack, controlStack);
}

TEST(TStack, can_copy_stack)
{
    TStack<int> stack1(5);
    stack1.push(123);
    stack1.push(999);
    stack1.push(100);
    TStack<int> stack2(stack1);

    ASSERT_EQ(stack1, stack2);
}

TEST(TStack, can_assign_stack)
{
    TStack<int> stack1(5);
    stack1.push(123);
    stack1.push(999);
    stack1.push(100);
    TStack<int> stack2(10);
    stack2 = stack1;

    ASSERT_EQ(stack1, stack2);
}

TEST(TStack, can_get_size)
{
    TStack<int> stack(5);
    stack.push(123);
    stack.push(999);
    stack.push(100);

    ASSERT_EQ(3, stack.getSize());
}

TEST(TStack, can_get_reserved)
{
    TStack<int> stack(5);

    ASSERT_EQ(5, stack.getReserved());
}

TEST(TStack, can_copy_rvalue_stack)
{
    TStack<int> stack1(5);
    stack1.push(123);
    stack1.push(999);
    stack1.push(100);
    TStack<int> controlStack(stack1);
    TStack<int> stack2(std::move(stack1));

    EXPECT_EQ(controlStack, stack2);
}

TEST(TStack, can_move_rvalue_stack)
{
    TStack<int> stack1(5);
    stack1.push(123);
    stack1.push(999);
    stack1.push(100);
    TStack<int> controlStack(stack1);
    TStack<int> stack2 = std::move(stack1);

    EXPECT_EQ(controlStack, stack2);
}

TEST(TStack, can_get_top_element)
{
    TStack<int> stack(5);
    stack.push(123);
    stack.push(999);
    stack.push(100);

    EXPECT_EQ(100, stack.back());
}

TEST(TStack, cant_get_top_element_of_an_empty_stack)
{
    TStack<int> stack(5);

    EXPECT_ANY_THROW(stack.back());
}

TEST(TStack, can_resize_stack_to_a_larger_size)
{
    TStack<int> stack(2);
    stack.push(123);
    stack.push(999);
    stack.resize(3);
    stack.push(100);

    TStack<int> controlStack(3);
    controlStack.push(123);
    controlStack.push(999);
    controlStack.push(100);

    EXPECT_EQ(3, stack.getReserved());
    EXPECT_EQ(controlStack, stack);
}

TEST(TStack, can_resize_stack_to_a_smaller_size_without_cutting_off)
{
    TStack<int> stack(5);
    stack.push(123);
    stack.push(999);
    stack.push(100);
    stack.resize(3);

    TStack<int> controlStack(3);
    controlStack.push(123);
    controlStack.push(999);
    controlStack.push(100);

    EXPECT_EQ(3, stack.getReserved());
    EXPECT_EQ(controlStack, stack);
}

TEST(TStack, can_resize_stack_to_a_smaller_size_and_cut_off_elements)
{
    TStack<int> stack(5);
    stack.push(123);
    stack.push(999);
    stack.push(100);
    stack.resize(2);

    TStack<int> controlStack(2);
    controlStack.push(123);
    controlStack.push(999);

    EXPECT_EQ(2, stack.getReserved());
    EXPECT_EQ(controlStack, stack);
}

TEST(TStack, can_push_to_a_full_stack)
{
    TStack<int> stack(2);
    stack.push(123);
    stack.push(999);
    stack.push(100);

    TStack<int> controlStack(2);
    controlStack.push(123);
    controlStack.push(999);
    controlStack.push(100);

    EXPECT_EQ(4, stack.getReserved());
    EXPECT_EQ(controlStack, stack);
}

TEST(TStack, can_pop_element)
{
    TStack<int> stack(5);
    stack.push(123);
    stack.push(999);
    stack.push(100);
    stack.pop();

    EXPECT_EQ(999, stack.back());
}

TEST(TStack, correct_size_after_popping)
{
    TStack<int> stack(5);
    stack.push(123);
    stack.push(999);
    stack.push(100);
    stack.pop();

    EXPECT_EQ(2, stack.getSize());
}

TEST(TStack, cant_pop_empty_stack)
{
    TStack<int> stack(5);
    
    EXPECT_ANY_THROW(stack.pop());
}

TEST(TStack, empty_is_true_when_empty)
{
    TStack<int> stack(5);
    stack.push(1);
    stack.pop();

    EXPECT_TRUE(stack.empty());
}

TEST(TStack, empty_is_false_when_not_empty)
{
    TStack<int> stack(5);
    stack.push(1);

    EXPECT_FALSE(stack.empty());
}