#pragma once
#include <iostream>

template <typename T>
class Pair {
private:
    T first;
    T second;

public:
    Pair();
    Pair(const T& a, const T& b);

    void set(const T& a, const T& b);
    T getFirst() const;
    T getSecond() const;

    bool isEqual() const;
    void print() const;
};

// Реализация шаблона

template <typename T>
Pair<T>::Pair() : first(), second() {}

template <typename T>
Pair<T>::Pair(const T& a, const T& b) : first(a), second(b) {}

template <typename T>
void Pair<T>::set(const T& a, const T& b) {
    first = a;
    second = b;
}

template <typename T>
T Pair<T>::getFirst() const {
    return first;
}

template <typename T>
T Pair<T>::getSecond() const {
    return second;
}

template <typename T>
bool Pair<T>::isEqual() const {
    return first == second;
}

template <typename T>
void Pair<T>::print() const {
    std::cout << "First: " << first << " | Second: " << second << "\n";
}
