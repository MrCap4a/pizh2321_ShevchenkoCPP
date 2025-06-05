#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Lesson.h"
#include "IndexOutOfBoundsException.h"

class Schedule {
private:
    std::string address;
    std::vector<Lesson*> lessons;

public:
    Schedule(const std::string& address);
    ~Schedule();

    void addLesson(Lesson* lesson);
    void show() const;

    Lesson* operator[](size_t index);
    friend std::ostream& operator<<(std::ostream& os, const Schedule& s);
};
