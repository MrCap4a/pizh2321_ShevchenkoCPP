#pragma once
#include <string>
#include <vector>
#include "Lesson.h"

class Schedule {
private:
    std::string address;
    std::vector<Lesson*> lessons;

public:
    Schedule(const std::string& address);
    ~Schedule();

    void addLesson(Lesson* lesson);
    void show() const;
};
