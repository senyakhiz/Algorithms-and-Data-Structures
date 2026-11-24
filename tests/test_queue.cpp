// Copyright 2026 Ksenia Kh

#include <gtest/gtest.h>
#include <stdexcept>
#include <algorithm>

#include "../lib_queue/queue.h"

TEST(Queue, can_create_queue) {
    Queue<int> queue(5);

    EXPECT_EQ(0u, queue.size());
    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}

TEST(Queue, can_create_queue_with_one_element_capacity) {
    Queue<int> queue(1);

    EXPECT_EQ(0u, queue.size());
    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}

TEST(Queue, empty_queue_is_empty) {
    Queue<int> queue(5);

    EXPECT_TRUE(queue.is_empty());
}

TEST(Queue, queue_is_not_empty_after_push) {
    Queue<int> queue(5);

    queue.push(10);

    EXPECT_FALSE(queue.is_empty());
}

TEST(Queue, queue_is_full_after_filling) {
    Queue<int> queue(3);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_TRUE(queue.is_full());
    EXPECT_EQ(3u, queue.size());
}

TEST(Queue, queue_is_not_full_after_pop) {
    Queue<int> queue(2);

    queue.push(10);
    queue.push(20);

    queue.pop();

    EXPECT_FALSE(queue.is_full());
}

TEST(Queue, can_push_element) {
    Queue<int> queue(5);

    queue.push(10);

    EXPECT_EQ(1u, queue.size());
    EXPECT_EQ(10, queue.front());
}

TEST(Queue, can_push_multiple_elements) {
    Queue<int> queue(5);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(3u, queue.size());
    EXPECT_EQ(10, queue.front());
}

TEST(Queue, cannot_push_into_full_queue) {
    Queue<int> queue(2);

    queue.push(10);
    queue.push(20);

    EXPECT_THROW(queue.push(30), std::overflow_error);
}

TEST(Queue, can_pop_element) {
    Queue<int> queue(5);

    queue.push(10);

    EXPECT_EQ(10, queue.pop());
    EXPECT_TRUE(queue.is_empty());
}

TEST(Queue, pop_returns_elements_in_fifo_order) {
    Queue<int> queue(5);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(10, queue.pop());
    EXPECT_EQ(20, queue.pop());
    EXPECT_EQ(30, queue.pop());
}

TEST(Queue, cannot_pop_from_empty_queue) {
    Queue<int> queue(5);

    EXPECT_THROW(queue.pop(), std::underflow_error);
}

TEST(Queue, size_decreases_after_pop) {
    Queue<int> queue(5);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    queue.pop();

    EXPECT_EQ(2u, queue.size());
}

TEST(Queue, front_returns_first_element) {
    Queue<int> queue(5);

    queue.push(10);
    queue.push(20);

    EXPECT_EQ(10, queue.front());
}

TEST(Queue, front_does_not_remove_element) {
    Queue<int> queue(5);

    queue.push(10);

    EXPECT_EQ(10, queue.front());
    EXPECT_EQ(1u, queue.size());
}

TEST(Queue, front_changes_after_pop) {
    Queue<int> queue(5);

    queue.push(10);
    queue.push(20);

    queue.pop();

    EXPECT_EQ(20, queue.front());
}

TEST(Queue, cannot_get_front_from_empty_queue) {
    Queue<int> queue(5);

    EXPECT_THROW(queue.front(), std::out_of_range);
}

TEST(Queue, can_copy_queue) {
    Queue<int> original(5);

    original.push(10);
    original.push(20);
    original.push(30);

    Queue<int> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(10, copy.front());
    EXPECT_EQ(10, copy.pop());
    EXPECT_EQ(20, copy.front());

    EXPECT_EQ(10, original.front());
}

TEST(Queue, can_copy_empty_queue) {
    Queue<int> original(5);

    Queue<int> copy(original);

    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(0u, copy.size());
}

TEST(Queue, copied_queues_are_independent) {
    Queue<int> original(5);

    original.push(10);
    original.push(20);

    Queue<int> copy(original);

    copy.pop();

    EXPECT_EQ(10, original.front());
    EXPECT_EQ(20, copy.front());
}

TEST(Queue, can_assign_queue) {
    Queue<int> original(5);
    Queue<int> copy(3);

    original.push(10);
    original.push(20);
    original.push(30);

    copy = original;

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(10, copy.front());
    EXPECT_EQ(10, original.front());
}

TEST(Queue, can_assign_queue_to_itself) {
    Queue<int> queue(5);

    queue.push(10);
    queue.push(20);

    queue = queue;

    EXPECT_EQ(2u, queue.size());
    EXPECT_EQ(10, queue.front());
}

TEST(Queue, assigned_queues_are_independent) {
    Queue<int> original(5);
    Queue<int> copy(3);

    original.push(10);
    original.push(20);

    copy = original;
    copy.pop();

    EXPECT_EQ(10, original.front());
    EXPECT_EQ(20, copy.front());
}

TEST(Queue, can_assign_empty_queue) {
    Queue<int> original(5);
    Queue<int> copy(3);

    copy.push(10);
    copy.push(20);

    copy = original;

    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(0u, copy.size());
}

TEST(Queue, can_reuse_freed_places) {
    Queue<int> queue(3);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    queue.pop();
    queue.pop();

    queue.push(40);
    queue.push(50);

    EXPECT_EQ(3u, queue.size());
    EXPECT_EQ(30, queue.front());
}

TEST(Queue, can_pop_elements_after_circular_movement) {
    Queue<int> queue(3);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    queue.pop();
    queue.pop();

    queue.push(40);
    queue.push(50);

    EXPECT_EQ(30, queue.pop());
    EXPECT_EQ(40, queue.pop());
    EXPECT_EQ(50, queue.pop());

    EXPECT_TRUE(queue.is_empty());
}

TEST(Queue, can_copy_queue_after_circular_movement) {
    Queue<int> original(3);

    original.push(10);
    original.push(20);
    original.push(30);

    original.pop();
    original.pop();

    original.push(40);
    original.push(50);

    Queue<int> copy(original);

    EXPECT_EQ(3u, copy.size());
    EXPECT_EQ(30, copy.pop());
    EXPECT_EQ(40, copy.pop());
    EXPECT_EQ(50, copy.pop());

    EXPECT_EQ(30, original.front());
}
