// Copyright 2026 Ksenia Kh

#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_

#include <cstddef>
#include <stdexcept>

template <class T>
class Queue {
    size_t _size;
    T* _data;
    size_t _front;
    size_t _back;
 public:
     explicit Queue(size_t size);
     Queue(const Queue& other);
     ~Queue();

     Queue& operator = (const Queue& other);

     size_t size() const;
     T& front();

     bool is_full() const;
     bool is_empty() const;

     void push(const T&);
     T pop();
};

template <class T>
Queue<T>::Queue(size_t size) :
    _size(size + 1),
    _data(new T[size + 1]),
    _front(0),
    _back(0) {
}

template <class T>
Queue<T>::Queue(const Queue& other) :
    _size(other._size),
    _data(new T[other._size]),
    _front(other._front),
    _back(other._back) {
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

template <class T>
Queue<T>::~Queue() {
    delete[] _data;
}

template <class T>
Queue<T>& Queue<T>::operator = (const Queue& other) {
    if (this == &other) {
        return *this;
    }
    T* new_data = new T[other._size];
    for (size_t i = 0; i < other._size; ++i) {
        new_data[i] = other._data[i];
    }
    delete[] _data;
    _data = new_data;
    _size = other._size;
    _front = other._front;
    _back = other._back;
    return *this;
}

template <class T>
size_t Queue<T>::size() const {
    return (_back - _front + _size) % _size;
}

template <class T>
T& Queue<T>::front() {
    if (is_empty()) {
        throw std::out_of_range("queue is empty");
    }
    return _data[_front];
}

template <class T>
bool Queue<T>::is_full() const {
    return (_back + 1) % _size == _front;
}

template <class T>
bool Queue<T>::is_empty() const {
    return _front == _back;
}

template <class T>
void Queue<T>::push(const T& value) {
    if (is_full()) {
        throw std::overflow_error("queue is full");
    }
    _data[_back] = value;
    _back = (_back + 1) % _size;
}

template <class T>
T Queue<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("queue is empty");
    }
    T value = _data[_front];
    _front = (_front + 1) % _size;
    return value;
}

#endif  // LIB_QUEUE_QUEUE_H_
