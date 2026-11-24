// Copyright 2026 Ksenia Kh

#ifndef LIB_STACK_ON_MASS_STACK_ON_MASS_H_
#define LIB_STACK_ON_MASS_STACK_ON_MASS_H_

#include <iostream>
#include <string>
#include <cstddef>
#include <stdexcept>

template <class T>
class TStackOnMass {
    T* _data;
    size_t _size;
    size_t _top;

 public:
     explicit TStackOnMass(size_t size);
     TStackOnMass(const TStackOnMass& other);
     ~TStackOnMass();

     void push(const T&);
     T pop();
     T& top();

     bool is_empty() const noexcept;
     bool is_full() const noexcept;

     bool check_breckets(std::string expression);
};

#endif  // LIB_STACK_ON_MASS_STACK_ON_MASS_H_

template <class T>
TStackOnMass<T>::TStackOnMass(size_t size) : _size(size), _top(0) {
    _data = new T[_size];
}

template <class T>
TStackOnMass<T>::TStackOnMass(const TStackOnMass& other) :
    _size(other._size), _top(other._top) {
    _data = new T[_size];
    for (size_t i = 0; i < _top; ++i) {
        _data[i] = other._data[i];
    }
}

template <class T>
TStackOnMass<T>::~TStackOnMass() {
    delete[] _data;
}

template <class T>
void TStackOnMass<T>::push(const T& value) {
    if (is_full()) {
        throw std::overflow_error("Stack overflow");
    }
    _data[_top++] = value;
}

template <class T>
T TStackOnMass<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("Stack underflow");
    }
    return _data[--_top];
}

template <class T>
T& TStackOnMass<T>::top() {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty");
    }
    return _data[_top - 1];
}

template <class T>
bool TStackOnMass<T>::is_empty() const noexcept {
    return _top == 0;
}

template <class T>
bool TStackOnMass<T>::is_full() const noexcept {
    return _top == _size;
}

template <class T>
bool TStackOnMass<T>::check_breckets(std::string expression) {
    size_t max_size = expression.length() > 0 ? expression.length() : 1;
    TStackOnMass<char> st(max_size);

    for (char c : expression) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (st.is_empty()) {
                return false;
            }
            char top_char = st.pop();
            if ((c == ')' && top_char != '(') ||
                (c == ']' && top_char != '[') ||
                (c == '}' && top_char != '{')) {
                return false;
            }
        }
    }
    return st.is_empty();
}
