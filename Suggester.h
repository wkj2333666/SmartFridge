#pragma once
#include <vector>

template <class T>
class Heap {
    std::vector<T> data;
public:
    Heap();
    ~Heap();
    void push_back(const T&);
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
    typename std::vector<T>::iterator begin();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator end() const;
};

template <class T>
class Heap<T*> {
    std::vector<T*> data;
public:
    Heap();
    ~Heap();
    void push_back(const T* const);
    void insert(const T* const);
    T* const borrowTop();
    const T* const borrowTop() const;
    T* extractTop();

private:
    void siftUp(int idx);
    void siftDown(int idx);

public:
    bool isEmpty();
    int size();
    typename std::vector<T>::iterator begin();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator end() const;
};