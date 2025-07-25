#pragma once
// #include <vector>
// #include "Suggester.h"
#include "config.h"
// #include <algorithm>
#include <cassert>

template <class T>
class Heap {
    T* data;
    int _end;
    int capacity;

    void expand();

public:
    Heap();
    ~Heap();
    void push_back(const T&);
    void pop_back();
    void insert(const T& element);
    T& borrowTop();
    const T& borrowTop() const;
    T extractTop();

private:
    void siftUp(int idx);
    void siftDown(int idx);

public:
    bool isEmpty();
    int size();
    T* const begin();
    const T* const begin() const;
    T* const end();
    const T* const end() const;
};

template <class T>
class Heap<T*> {
    T** data;
    int _end;
    int capacity;

    using Heap<T>::expand;
public:
    Heap();
    ~Heap();
    void push_back(const T* const);
    using Heap<T>::pop_back;
    void insert(const T* const);
    T* const borrowTop();
    const T* const borrowTop() const;
    T* extractTop();

private:
    void siftUp(int idx);
    void siftDown(int idx);

public:
    using Heap<T>::isEmpty;
    using Heap<T>::size;
    using Heap<T>::begin;
    // using Heap<T>::begin const;
    using Heap<T>::end;
    // using Heap<T>::end const;
};


template <class T>
Heap<T>::Heap(): 
    data(new T[DEFAULT_QUEUE_LENGTH + 1]),
    _end(1),
    capacity(DEFAULT_QUEUE_LENGTH + 1)
{}

template <class T>
Heap<T>::~Heap() {
    delete[] data;
}

template <class T>
void Heap<T>::expand() {
    capacity *= 2;
    T* new_data = new T[capacity];
    for (int idx = 1; idx != end; idx++) {
        new_data[idx] = data[idx];
    }
    delete[] data;
    data = new_data;
}

template <class T>
bool Heap<T>::isEmpty() {
    return end == 1;
}

template <class T>
int Heap<T>::size() {
    return end - 1;
}

template <class T>
T* const Heap<T>::begin() {
    return data + 1;
}

template <class T>
T* const Heap<T>::end() {
    return data + end;
}

template <class T>
const T* const Heap<T>::begin() const{
    return data + 1;
}

template <class T>
const T* const Heap<T>::end() const{
    return data + end;
}

template <class T>
void Heap<T>::push_back(const T& element) {
    if (end == capacity) expand();
    data[end++] = element;
}

template <class T>
T& Heap<T>::borrowTop() {
    assert(end > 1);
    return data[1];
}

template <class T>
const T& Heap<T>::borrowTop() const {
    assert(end > 1);
    return data[1];
}

template <class T>
void Heap<T>::insert(const T& element) {
    if (end == 1) {
        push_back(element);
        return;
    }

    int idx = end;
    push_back(element);
    siftUp(idx);
}

template <class T>
T Heap<T>::extractTop() {
    assert(end > 1);
    T top = data[1];
    data[1] = data[end - 1];
    pop_back();
    siftDown(1);
    return top;
}

template <class T>
void Heap<T>::siftUp(int idx) {
    assert(idx > 1 && idx < end);
    if (idx == 1) return;

    int parent = idx / 2;
    if (data[parent] > data[idx]) {
        T tmp = data[idx];
        data[idx] = data[parent];
        data[parent] = tmp;
        siftUp(parent);
    }
}

template <class T>
void Heap<T>::siftDown(int idx) {
    assert(end > 1);
    int idx_left = 2 * idx;
    if (idx_left >= end) return;

    // find idx_less, idx_bigger
    int idx_less = idx_left;
    int idx_bigger = idx_left;
    if (idx_left + 1 < end) { // idx has right node
        int idx_right = idx_left + 1;
        idx_less = data[idx_left] > data[idx_right] ? idx_right : idx_left;
        idx_bigger = data[idx_left] > data[idx_right] ? idx_left : idx_right;
    }

    if (data[idx] > data[idx_bigger]) {
        T tmp = data[idx];
        data[idx] = data[idx_less];
        data[idx_less] = tmp;
        siftDown(idx_less);
    }
}


template <class T>
Heap<T*>::Heap(): 
    data(new T*[DEFAULT_QUEUE_LENGTH + 1]),
    _end(1),
    capacity(DEFAULT_QUEUE_LENGTH + 1)
{}

template <class T>
Heap<T*>::~Heap() {
    // free memory
    for (int idx = 1; idx != _end; idx++) {
        delete data[idx];
    }
    delete data;
}

// template <class T>
// bool Heap<T*>::isEmpty() {
//     return end == 1;
// }

// template <class T>
// int Heap<T*>::size() {
//     return end - 1;
// }

// template <class T>
// typename std::vector<T>::iterator Heap<T*>::begin() {
//     return ++data.begin();
// }

// template <class T>
// typename std::vector<T>::iterator Heap<T*>::end() {
//     return data.end();
// }

// template <class T>
// typename std::vector<T>::const_iterator Heap<T*>::begin() const{
//     return ++data.cbegin();
// }

// template <class T>
// typename std::vector<T>::const_iterator Heap<T*>::end() const {
//     return data.cend();
// }

template <class T>
void Heap<T*>::push_back(const T* const element) {
    if (_end == capacity) expand();

    data[_end++] = element;
}

// template <class T>
// void Heap<T*>::pop_back() {
//     assert(_end > 1);
//     _end--;
// }

template <class T>
T* const Heap<T*>::borrowTop() {
    assert(_end > 1);
    return data[1];
}

template <class T>
const T* const Heap<T*>::borrowTop() const {
    assert(_end > 1);
    return data[1];
}

template <class T>
void Heap<T*>::insert(const T* const element) {
    if (_end == 1) {
        push_back(element);
        return;
    }

    int idx = _end;
    push_back(element);
    siftUp(idx);
}

template <class T>
T* Heap<T*>::extractTop() {
    // give away ownership
    assert(_end > 1);
    T* top = data[1];
    data[1] = data[_end - 1];
    pop_back();
    siftDown(1);
    return top;
}

template <class T>
void Heap<T*>::siftUp(int idx) {
    assert(idx > 1 && idx < _end);
    if (idx == 1) return;

    int parent = idx / 2;
    if (*data[parent] > *data[idx]) {
        T* tmp = data[idx];
        data[idx] = data[parent];
        data[parent] = tmp;
        siftUp(parent);
    }
}

template <class T>
void Heap<T*>::siftDown(int idx) {
    assert(_end > 1);
    int idx_left = 2 * idx;
    if (idx_left >= _end) return;

    // find idx_less, idx_bigger
    int idx_less = idx_left;
    int idx_bigger = idx_left;
    if (idx_left + 1 < _end) { // idx has right node
        int idx_right = idx_left + 1;
        idx_less = *data[idx_left] > *data[idx_right] ? idx_right : idx_left;
        idx_bigger = *data[idx_left] > *data[idx_right] ? idx_left : idx_right;
    }

    if (*data[idx] > *data[idx_bigger]) {
        T* tmp = data[idx];
        data[idx] = data[idx_less];
        data[idx_less] = tmp;
        siftDown(idx_less);
    }
}