// Copyright 2026 Ksenia Kh
#include <gtest/gtest.h>
#define VECTOR_TESTS

#ifdef MEMDATA_TESTS
#include "../lib_vector/memdata.h"
#include "../lib_vector/vector.h"

TEST(FunctionsForMemData, calculate_capacity) {
    EXPECT_EQ(0, calculate_capacity(0));
    EXPECT_EQ(15, calculate_capacity(1));
    EXPECT_EQ(15, calculate_capacity(15));
    EXPECT_EQ(30, calculate_capacity(16));
    EXPECT_EQ(30, calculate_capacity(30));
    EXPECT_EQ(45, calculate_capacity(31));
}

TEST(ClassMemData, can_create_with_default_constructor) {
    MemData<double> data;

    EXPECT_EQ(0, data.size());
    EXPECT_EQ(0, data.capacity());
    EXPECT_TRUE(data.is_empty());
    EXPECT_FALSE(data.is_full());
    EXPECT_EQ(nullptr, data.data());
}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    MemData<double> data(10);

    EXPECT_EQ(0, data.size());
    EXPECT_EQ(15, data.capacity());
    EXPECT_TRUE(data.is_empty());
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    MemData<double> data({ 1, 2, 3, 4, 5 });

    EXPECT_EQ(5, data.size());
    EXPECT_EQ(15, data.capacity());

    for (size_t i = 0; i < data.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, data.data()[i]);
    }
}

TEST(ClassMemData, can_create_with_init_constructor) {
    double arr[] = { 10, 20, 30, 40 };

    MemData<double> data(arr, 4);

    EXPECT_EQ(4, data.size());
    EXPECT_EQ(15, data.capacity());

    for (size_t i = 0; i < data.size(); i++) {
        EXPECT_DOUBLE_EQ(arr[i], data.data()[i]);
    }
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    MemData<double> original({ 1, 2, 3, 4 });
    MemData<double> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());

    for (size_t i = 0; i < original.size(); i++) {
        EXPECT_DOUBLE_EQ(original.data()[i], copy.data()[i]);
    }

    EXPECT_NE(original.data(), copy.data());
}

TEST(ClassMemData, can_create_with_move_constructor) {
    MemData<double> original({ 1, 2, 3 });

    MemData<double> moved(std::move(original));

    EXPECT_EQ(0, original.size());
    EXPECT_EQ(0, original.capacity());
    EXPECT_EQ(nullptr, original.data());

    EXPECT_EQ(3, moved.size());
    EXPECT_EQ(15, moved.capacity());
}

TEST(ClassMemData, can_is_empty) {
    MemData<double> data;

    EXPECT_TRUE(data.is_empty());

    data.set_size_for_test(5);

    EXPECT_FALSE(data.is_empty());
}

TEST(ClassMemData, can_is_full) {
    MemData<double> data(15);

    EXPECT_FALSE(data.is_full());

    data.set_size_for_test(15);

    EXPECT_TRUE(data.is_full());
}

TEST(ClassMemData, can_set_memory_for_empty) {
    MemData<double> data;

    data.set_memory(20);

    EXPECT_EQ(0, data.size());
    EXPECT_EQ(20, data.capacity());
    EXPECT_TRUE(data.is_empty());
    EXPECT_NE(nullptr, data.data());
}

TEST(ClassMemData, can_set_memory_for_not_empty) {
    MemData<double> data({ 1, 2, 3, 4, 5 });

    data.set_memory(30);

    EXPECT_EQ(0, data.size());
    EXPECT_EQ(30, data.capacity());
    EXPECT_TRUE(data.is_empty());
    EXPECT_NE(nullptr, data.data());
}

TEST(ClassMemData, can_set_memory_without_reallocation) {
    MemData<double> data;

    data.set_memory(15);
    const double* first = data.data();

    data.set_memory(15);

    EXPECT_EQ(15, data.capacity());
    EXPECT_EQ(0, data.size());
    EXPECT_NE(nullptr, data.data());
    EXPECT_NE(first, data.data());
}

TEST(ClassMemData, can_reset_memory_for_empty) {
    MemData<double> data;

    data.reset_memory(20);

    EXPECT_EQ(0, data.size());
    EXPECT_EQ(30, data.capacity());
    EXPECT_TRUE(data.is_empty());
}

TEST(ClassMemData, can_reset_memory_for_not_empty_increase) {
    MemData<double> data({ 1, 2, 3, 4, 5 });

    data.reset_memory(20);

    EXPECT_EQ(5, data.size());
    EXPECT_EQ(30, data.capacity());

    for (size_t i = 0; i < data.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, data.data()[i]);
    }
}

TEST(ClassMemData, can_reset_memory_for_not_empty_decrease) {
    MemData<double> data({ 1, 2, 3, 4, 5, 6, 7, 8 });

    data.reset_memory(4);

    EXPECT_EQ(4, data.size());
    EXPECT_EQ(15, data.capacity());

    for (size_t i = 0; i < data.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, data.data()[i]);
    }
}

TEST(ClassMemData, can_reset_memory_without_reallocation) {
    MemData<double> data({ 1, 2, 3, 4, 5 });

    data.reset_memory(10);

    const double* first = data.data();

    data.reset_memory(12);

    EXPECT_EQ(5, data.size());
    EXPECT_EQ(15, data.capacity());
    EXPECT_NE(first, data.data());

    for (size_t i = 0; i < data.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, data.data()[i]);
    }
}

TEST(ClassMemData, can_reset_memory_with_shift) {
    MemData<double> data({ 1, 2, 3, 4, 5, 6, 7, 8 });

    data.reset_memory(5, 3);

    EXPECT_EQ(5, data.size());
    EXPECT_EQ(15, data.capacity());

    for (size_t i = 0; i < data.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 4, data.data()[i]);
    }
}

TEST(ClassMemData, can_clear_memory_for_empty) {
    MemData<double> data;

    data.clear_memory();

    EXPECT_EQ(0, data.size());
    EXPECT_EQ(0, data.capacity());
    EXPECT_TRUE(data.is_empty());
    EXPECT_EQ(nullptr, data.data());
}

TEST(ClassMemData, can_clear_memory_for_not_empty) {
    MemData<double> data({ 1, 2, 3, 4, 5 });

    data.clear_memory();

    EXPECT_EQ(0, data.size());
    EXPECT_EQ(0, data.capacity());
    EXPECT_TRUE(data.is_empty());
    EXPECT_EQ(nullptr, data.data());
}

TEST(ClassMemData, can_assigment) {
    MemData<double> original({ 1, 2, 3, 4, 5 });
    MemData<double> copy;

    copy = original;

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());
    EXPECT_NE(original.data(), copy.data());

    for (size_t i = 0; i < original.size(); i++) {
        EXPECT_DOUBLE_EQ(original.data()[i], copy.data()[i]);
    }
}

TEST(ClassMemData, can_move_assigment) {
    MemData<double> original({ 1, 2, 3, 4, 5 });
    MemData<double> moved;

    moved = std::move(original);

    EXPECT_EQ(0, original.size());
    EXPECT_EQ(0, original.capacity());
    EXPECT_EQ(nullptr, original.data());

    EXPECT_EQ(5, moved.size());
    EXPECT_EQ(15, moved.capacity());

    for (size_t i = 0; i < moved.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, moved.data()[i]);
    }
}

#endif

#ifdef VECTOR_TESTS
#include "vector.h"

TEST(ClassVector, can_create_with_default_constructor) {
    Vector<double> vec;

    EXPECT_TRUE(vec.is_empty());
    EXPECT_FALSE(vec.is_full());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.capacity());
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    Vector<double> vec(10);

    EXPECT_TRUE(vec.is_empty());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(15, vec.capacity());
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    Vector<double> vec({ 1, 2, 3, 4, 5 });

    EXPECT_FALSE(vec.is_empty());
    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_create_with_init_constructor) {
    double arr[] = { 1, 2, 3, 4, 5 };

    Vector<double> vec(arr, 5);

    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(arr[i], vec[i]);
    }
}

TEST(ClassVector, can_create_with_copy_constructor) {
    Vector<double> original({ 1, 2, 3, 4, 5 });
    Vector<double> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());

    for (size_t i = 0; i < original.size(); i++) {
        EXPECT_DOUBLE_EQ(original[i], copy[i]);
    }

    copy[0] = 100;

    EXPECT_DOUBLE_EQ(1, original[0]);
    EXPECT_DOUBLE_EQ(100, copy[0]);
}

TEST(ClassVector, can_create_with_move_constructor) {
    Vector<double> original({ 1, 2, 3, 4, 5 });
    Vector<double> moved(std::move(original));

    EXPECT_EQ(0, original.size());
    EXPECT_EQ(0, original.capacity());

    EXPECT_EQ(5, moved.size());
    EXPECT_EQ(15, moved.capacity());

    for (size_t i = 0; i < moved.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, moved[i]);
    }
}

TEST(ClassVector, can_is_empty) {
    Vector<double> vec;

    EXPECT_TRUE(vec.is_empty());

    vec.push_back(10);

    EXPECT_FALSE(vec.is_empty());

    vec.pop_back();

    EXPECT_TRUE(vec.is_empty());
}

TEST(ClassVector, can_is_full) {
    Vector<double> vec(15);

    EXPECT_FALSE(vec.is_full());

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i);
    }

    EXPECT_TRUE(vec.is_full());
}

TEST(ClassVector, can_get_front) {
    Vector<double> vec({ 10, 20, 30 });

    EXPECT_DOUBLE_EQ(10, vec.front());
}

TEST(ClassVector, can_get_back) {
    Vector<double> vec({ 10, 20, 30 });

    EXPECT_DOUBLE_EQ(30, vec.back());
}

TEST(ClassVector, can_set_front) {
    Vector<double> vec({ 10, 20, 30 });

    vec.front() = 100;

    EXPECT_DOUBLE_EQ(100, vec.front());
    EXPECT_DOUBLE_EQ(20, vec[1]);
}

TEST(ClassVector, can_set_back) {
    Vector<double> vec({ 10, 20, 30 });

    vec.back() = 300;

    EXPECT_DOUBLE_EQ(300, vec.back());
    EXPECT_DOUBLE_EQ(20, vec[1]);
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    Vector<double> vec;

    EXPECT_ANY_THROW(vec.front());
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    Vector<double> vec;

    EXPECT_ANY_THROW(vec.back());
}

TEST(ClassVector, throw_when_try_set_front_in_empty_vector) {
    Vector<double> vec;

    EXPECT_ANY_THROW(vec.front() = 10);
}

TEST(ClassVector, throw_when_try_set_back_in_empty_vector) {
    Vector<double> vec;

    EXPECT_ANY_THROW(vec.back() = 10);
}

TEST(ClassVector, can_output_with_operator_cout) {
    Vector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_input_with_operator_cin) {
    Vector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_push_front) {
    Vector<double> vec({ 2, 3, 4 });

    vec.push_front(1);

    EXPECT_EQ(4, vec.size());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_push_front_in_empty_vector) {
    Vector<double> vec;

    vec.push_front(10);

    EXPECT_EQ(1, vec.size());
    EXPECT_DOUBLE_EQ(10, vec.front());
    EXPECT_DOUBLE_EQ(10, vec.back());
}

TEST(ClassVector, can_push_front_with_reallocation) {
    Vector<double> vec(15);

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.push_front(0);

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(0, vec.front());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i, vec[i]);
    }
}

TEST(ClassVector, can_push_back) {
    Vector<double> vec({ 1, 2, 3 });

    vec.push_back(4);

    EXPECT_EQ(4, vec.size());
    EXPECT_DOUBLE_EQ(4, vec.back());
}

TEST(ClassVector, can_push_back_in_empty_vector) {
    Vector<double> vec;

    vec.push_back(10);

    EXPECT_EQ(1, vec.size());
    EXPECT_DOUBLE_EQ(10, vec.front());
    EXPECT_DOUBLE_EQ(10, vec.back());
}

TEST(ClassVector, can_push_back_with_reallocation) {
    Vector<double> vec(15);

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.push_back(16);

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(16, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_insert) {
    Vector<double> vec({ 1, 2, 4, 5 });

    vec.insert(3, 2);

    EXPECT_EQ(5, vec.size());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_insert_with_reallocation) {
    Vector<double> vec(15);

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.insert(100, 5);

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(100, vec[5]);
}

TEST(ClassVector, can_insert_to_front) {
    Vector<double> vec({ 2, 3, 4 });

    vec.insert(1, 0);

    EXPECT_EQ(4, vec.size());
    EXPECT_DOUBLE_EQ(1, vec.front());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    Vector<double> vec({ 1, 2, 3 });

    EXPECT_ANY_THROW(vec.insert(10, 5));
}

TEST(ClassVector, can_pop_front) {
    Vector<double> vec({ 1, 2, 3, 4 });

    vec.pop_front();

    EXPECT_EQ(3, vec.size());
    EXPECT_DOUBLE_EQ(2, vec.front());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 2, vec[i]);
    }
}

TEST(ClassVector, can_pop_front_with_reallocation) {
    Vector<double> vec(16);

    for (size_t i = 0; i < 16; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_front();

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(2, vec.front());
}

TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    Vector<double> vec;

    EXPECT_ANY_THROW(vec.pop_front());
}

TEST(ClassVector, can_pop_back) {
    Vector<double> vec({ 1, 2, 3, 4 });

    vec.pop_back();

    EXPECT_EQ(3, vec.size());
    EXPECT_DOUBLE_EQ(3, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_pop_back_with_reallocation) {
    Vector<double> vec(16);

    for (size_t i = 0; i < 16; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_back();

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(15, vec.back());
}

TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    Vector<double> vec;

    EXPECT_ANY_THROW(vec.pop_back());
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_front();
    vec.push_back(16);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }

    vec.pop_back();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
}

TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_back();
    vec.push_front(0);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(0, vec.front());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i, vec[i]);
    }
}

TEST(ClassVector, can_erase) {
    Vector<double> vec({ 1, 2, 3, 4, 5 });

    vec.erase(2);

    EXPECT_EQ(4, vec.size());

    EXPECT_DOUBLE_EQ(1, vec[0]);
    EXPECT_DOUBLE_EQ(2, vec[1]);
    EXPECT_DOUBLE_EQ(4, vec[2]);
    EXPECT_DOUBLE_EQ(5, vec[3]);
}

TEST(ClassVector, can_erase_front) {
    Vector<double> vec({ 1, 2, 3, 4 });

    vec.erase(0);

    EXPECT_EQ(3, vec.size());
    EXPECT_DOUBLE_EQ(2, vec.front());
}

TEST(ClassVector, can_erase_back) {
    Vector<double> vec({ 1, 2, 3, 4 });

    vec.erase(3);

    EXPECT_EQ(3, vec.size());
    EXPECT_DOUBLE_EQ(3, vec.back());
}

TEST(ClassVector, can_erase_with_reallocation) {
    Vector<double> vec(16);

    for (size_t i = 0; i < 16; i++) {
        vec.push_back(i + 1);
    }

    vec.erase(5);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < 5; i++) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }

    for (size_t i = 5; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 2, vec[i]);
    }
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    Vector<double> vec;

    EXPECT_ANY_THROW(vec.erase(0));
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    Vector<double> vec({ 1, 2, 3 });

    EXPECT_ANY_THROW(vec.erase(3));
}

TEST(ClassVector, combination_push_pop_insert_erase) {
    Vector<double> vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_back(8 + i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.push_back(12 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_assigment) {
    Vector<double> original({ 1, 2, 3, 4, 5 });
    Vector<double> copy;

    copy = original;

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());

    for (size_t i = 0; i < original.size(); i++) {
        EXPECT_DOUBLE_EQ(original[i], copy[i]);
    }

    copy[0] = 100;

    EXPECT_DOUBLE_EQ(1, original[0]);
    EXPECT_DOUBLE_EQ(100, copy[0]);
}

TEST(ClassVector, can_move_assigment) {
    Vector<double> vec_1;
    Vector<double> vec_2;

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + i);
    }

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - i);
    }

    vec_2 = std::move(vec_1);

    EXPECT_EQ(0, vec_1.size());
    EXPECT_EQ(0, vec_1.capacity());

    EXPECT_EQ(8, vec_2.size());
    EXPECT_EQ(15, vec_2.capacity());

    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(vec_2[i], i + 1);
    }
}

#endif
