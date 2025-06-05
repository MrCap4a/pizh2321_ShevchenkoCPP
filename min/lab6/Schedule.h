#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Lesson.h"

class Schedule {
private:
    std::string address;
    std::vector<Lesson*> lessons;

public:
    Schedule(const std::string& address);
    Schedule(const Schedule& other);
    Schedule& operator=(const Schedule& other);
    ~Schedule();

    void addLesson(Lesson* lesson);
    void show() const;

    // Перегруженные операторы
    Schedule& operator+(Lesson* lesson);
    Schedule& operator++();       // Префикс
    Schedule& operator++(int);    // Постфикс — исправлено
    Lesson* operator[](size_t index);
    friend std::ostream& operator<<(std::ostream& os, const Schedule& s);
};
