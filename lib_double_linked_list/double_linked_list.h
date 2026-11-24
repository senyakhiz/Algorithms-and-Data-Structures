// Copyright 2026 Ksenia Kh

#ifndef LIB_DOUBLE_LINKED_LIST_DOUBLE_LINKED_LIST_H_
#define LIB_DOUBLE_LINKED_LIST_DOUBLE_LINKED_LIST_H_

#include <iostream>

template <typename T> struct Node {
    T _data;
    Node* _next;
    Node* _prev;
};

#endif // LIB_DOUBLE_LINKED_LIST_DOUBLE_LINKED_LIST_H_
