#pragma once
#include <iostream>

template <typename T>
class Pair<T*> {
private:
    T* first;
    T* second;

public:
    Pair();
    Pair(T* a, T* b);

    void set(T* a, T* b);
    T* getFirst() const;
    T* getSecond() const;

    bool isEqual() const;
    void print() const;
};

template <typename T>
Pair<T*>::Pair() : first(nullptr), second(nullptr) {}

template <typename T>
Pair<T*>::Pair(T* a, T* b) : first(a), second(b) {}

template <typename T>
void Pair<T*>::set(T* a, T* b) {
    first = a;
    second = b;
}

template <typename T>
T* Pair<T*>::getFirst() const {
    return first;
}

template <typename T>
T* Pair<T*>::getSecond() const {
    return second;
}

template <typename T>
bool Pair<T*>::isEqual() const {
    if (!first || !second) return false;
    return *first == *second;
}

template <typename T>
void Pair<T*>::print() const {
    std::cout << "Pointer Pair: ";
    if (first) std::cout << "[1] "; first->print();
    if (second) std::cout << "[2] "; second->print();
}
