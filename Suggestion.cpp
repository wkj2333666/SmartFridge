#include "Suggester.h"
#include "config.h"
#include <algorithm>
#include <cassert>

template <class T>
Heap<T>::Heap(): data(1) {}

template <class T>
Heap<T>::~Heap() {}

template <class T>
bool Heap<T>::isEmpty() {
    return data.size() == 1;
}

template <class T>
int Heap<T>::size() {
    return data.size() - 1;
}

template <class T>
typename std::vector<T>::iterator Heap<T>::begin() {
    return ++data.begin();
}

template <class T>
typename std::vector<T>::iterator Heap<T>::end() {
    return data.end();
}

template <class T>
typename std::vector<T>::const_iterator Heap<T>::begin() const{
    return ++data.cbegin();
}

template <class T>
typename std::vector<T>::const_iterator Heap<T>::end() const {
    return data.cend();
}

template <class T>
void Heap<T>::push_back(const T& element) {
    data.push_back(element);
}

template <class T>
T& Heap<T>::borrowTop() {
    assert data.size() > 1;
    return data[1];
}

template <class T>
const T& Heap<T>::borrowTop() const {
    assert data.size() > 1;
    return data[1];
}

template <class T>
void Heap<T>::insert(const T& element) {
    if (data.size() == 1) {
        data.push_back(element);
        return;
    }

    idx = data.size();
    data.push_back(element);
    siftUp(idx);
}

template <class T>
T Heap<T>::extractTop() {
    assert data.size() > 1;
    top = data[1];
    data[1] = data.back();
    data.pop_back();
    siftDown(1);
    return top;
}

template <class T>
void Heap<T>::siftUp(int idx) {
    assert idx > 1 && idx < data.size();
    if (idx == 1) return;

    int parent = idx / 2;
    if (data[parent] > data[idx]) {
        swap(data[idx], data[parent]);
        siftUp(parent);
    }
}

template <class T>
void Heap<T>::siftDown(int idx) {
    assert data.size() > 1;
    int idx_left = 2 * idx;
    if (idx_left >= data.size()) return;

    // find idx_less, idx_bigger
    int idx_less = idx_left;
    int idx_bigger = idx_left;
    if (idx_left + 1 < data.size()) { // idx has right node
        int idx_right = idx_left + 1;
        idx_less = data[idx_left] > data[idx_right] ? idx_right : idx_left;
        idx_bigger = data[idx_left] > data[idx_right] ? idx_left : idx_right;
    }

    if (data[idx] > data[idx_bigger]) {
        swap(data[idx], data[idx_less]);
        siftDown(idx_less);
    }
}


template <class T>
Heap<T*>::Heap(): data() {
    data.push_back(nullptr);
}

template <class T>
Heap<T*>::~Heap() {
    // free memory
    for (auto it = ++data.begin(); it != data.end(); it++) {
        delete *it;
    }
}

template <class T>
bool Heap<T*>::isEmpty() {
    return data.size() == 1;
}

template <class T>
int Heap<T*>::size() {
    return data.size() - 1;
}

template <class T>
typename std::vector<T>::iterator Heap<T*>::begin() {
    return ++data.begin();
}

template <class T>
typename std::vector<T>::iterator Heap<T*>::end() {
    return data.end();
}

template <class T>
typename std::vector<T>::const_iterator Heap<T*>::begin() const{
    return ++data.cbegin();
}

template <class T>
typename std::vector<T>::const_iterator Heap<T*>::end() const {
    return data.cend();
}

template <class T>
void Heap<T*>::push_back(const T* const) {
    data.push_back(element);
}

template <class T>
T* const Heap<T*>::borrowTop() {
    assert data.size() > 1;
    return data[1];
}

template <class T>
const T* const Heap<T*>::borrowTop() const {
    assert data.size() > 1;
    return data[1];
}

template <class T>
void Heap<T*>::insert(const T* const element) {
    if (data.size() == 1) {
        data.push_back(element);
        return;
    }

    idx = data.size();
    data.push_back(element);
    siftUp(idx);
}

template <class T>
T* Heap<T*>::extractTop() {
    // give away ownership
    assert data.size() > 1;
    top = data[1];
    data[1] = data.back();
    data.pop_back();
    siftDown(1);
    return top;
}

template <class T>
void Heap<T*>::siftUp(int idx) {
    assert idx > 1 && idx < data.size();
    if (idx == 1) return;

    int parent = idx / 2;
    if (*data[parent] > *data[idx]) {
        swap(data[idx], data[parent]);
        siftUp(parent);
    }
}

template <class T>
void Heap<T*>::siftDown(int idx) {
    assert data.size() > 1;
    int idx_left = 2 * idx;
    if (idx_left >= data.size()) return;

    // find idx_less, idx_bigger
    int idx_less = idx_left;
    int idx_bigger = idx_left;
    if (idx_left + 1 < data.size()) { // idx has right node
        int idx_right = idx_left + 1;
        idx_less = *data[idx_left] > *data[idx_right] ? idx_right : idx_left;
        idx_bigger = *data[idx_left] > *data[idx_right] ? idx_left : idx_right;
    }

    if (*data[idx] > *data[idx_bigger]) {
        swap(data[idx], data[idx_less]);
        siftDown(idx_less);
    }
}