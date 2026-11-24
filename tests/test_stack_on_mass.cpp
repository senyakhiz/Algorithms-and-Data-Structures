// Copyright 2026 Ksenia Kh

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "../lib_stack_on_mass/stack_on_mass.h"


TEST(TStackOnMass, can_create_stack) {
    TStackOnMass<int> stack(5);

    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(TStackOnMass, can_create_empty_stack) {
    TStackOnMass<int> stack(0);

    EXPECT_TRUE(stack.is_empty());
    EXPECT_TRUE(stack.is_full());
}

TEST(TStackOnMass, can_create_stack_with_different_types) {
    TStackOnMass<double> stack(3);

    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(TStackOnMass, can_copy_stack) {
    TStackOnMass<int> stack(5);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    TStackOnMass<int> copy(stack);

    EXPECT_FALSE(copy.is_empty());
    EXPECT_EQ(30, copy.top());
    EXPECT_EQ(30, copy.pop());
    EXPECT_EQ(20, copy.top());
    EXPECT_EQ(30, stack.top());
}

TEST(TStackOnMass, copied_stack_is_independent) {
    TStackOnMass<int> stack(5);

    stack.push(10);
    stack.push(20);

    TStackOnMass<int> copy(stack);

    copy.pop();

    EXPECT_EQ(20, stack.top());
    EXPECT_EQ(10, copy.top());
}

TEST(TStackOnMass, can_push_element) {
    TStackOnMass<int> stack(3);

    stack.push(10);

    EXPECT_FALSE(stack.is_empty());
    EXPECT_EQ(10, stack.top());
}

TEST(TStackOnMass, can_push_multiple_elements) {
    TStackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_TRUE(stack.is_full());
    EXPECT_EQ(30, stack.top());
}

TEST(TStackOnMass, can_push_elements_of_different_types) {
    TStackOnMass<double> stack(2);

    stack.push(1.5);
    stack.push(2.5);

    EXPECT_DOUBLE_EQ(2.5, stack.top());
}

TEST(TStackOnMass, throws_when_push_to_full_stack) {
    TStackOnMass<int> stack(2);

    stack.push(10);
    stack.push(20);

    EXPECT_THROW(stack.push(30), std::overflow_error);
}

TEST(TStackOnMass, can_pop_element) {
    TStackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);

    EXPECT_EQ(20, stack.pop());
    EXPECT_EQ(10, stack.top());
}

TEST(TStackOnMass, can_pop_all_elements) {
    TStackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(30, stack.pop());
    EXPECT_EQ(20, stack.pop());
    EXPECT_EQ(10, stack.pop());

    EXPECT_TRUE(stack.is_empty());
}

TEST(TStackOnMass, throws_when_pop_from_empty_stack) {
    TStackOnMass<int> stack(3);

    EXPECT_THROW(stack.pop(), std::underflow_error);
}

TEST(TStackOnMass, can_get_top_element) {
    TStackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);

    EXPECT_EQ(20, stack.top());
}

TEST(TStackOnMass, can_change_top_element) {
    TStackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);

    stack.top() = 100;

    EXPECT_EQ(100, stack.top());
}

TEST(TStackOnMass, throws_when_get_top_from_empty_stack) {
    TStackOnMass<int> stack(3);

    EXPECT_THROW(stack.top(), std::underflow_error);
}

TEST(TStackOnMass, can_check_empty_stack) {
    TStackOnMass<int> stack(3);

    EXPECT_TRUE(stack.is_empty());

    stack.push(10);

    EXPECT_FALSE(stack.is_empty());

    stack.pop();

    EXPECT_TRUE(stack.is_empty());
}

TEST(TStackOnMass, can_check_full_stack) {
    TStackOnMass<int> stack(2);

    EXPECT_FALSE(stack.is_full());

    stack.push(10);
    EXPECT_FALSE(stack.is_full());

    stack.push(20);
    EXPECT_TRUE(stack.is_full());

    stack.pop();
    EXPECT_FALSE(stack.is_full());
}

TEST(TStackOnMass, brackets_are_correct) {
    TStackOnMass<int> stack(10);

    EXPECT_TRUE(stack.check_breckets("()"));
    EXPECT_TRUE(stack.check_breckets("[]"));
    EXPECT_TRUE(stack.check_breckets("{}"));
    EXPECT_TRUE(stack.check_breckets("({[]})"));
}

TEST(TStackOnMass, brackets_are_correct_with_text) {
    TStackOnMass<int> stack(10);

    EXPECT_TRUE(stack.check_breckets("a + (b * c)"));
    EXPECT_TRUE(stack.check_breckets("function(a, [b, c])"));
}

TEST(TStackOnMass, brackets_are_incorrect) {
    TStackOnMass<int> stack(10);

    EXPECT_FALSE(stack.check_breckets("("));
    EXPECT_FALSE(stack.check_breckets(")"));
    EXPECT_FALSE(stack.check_breckets("([)]"));
    EXPECT_FALSE(stack.check_breckets("{]"));
    EXPECT_FALSE(stack.check_breckets("((())"));
}

TEST(TStackOnMass, empty_expression_has_correct_brackets) {
    TStackOnMass<int> stack(10);

    EXPECT_TRUE(stack.check_breckets(""));
}

TEST(TStackOnMass, expression_without_brackets_is_correct) {
    TStackOnMass<int> stack(10);

    EXPECT_TRUE(stack.check_breckets("hello world"));
}
