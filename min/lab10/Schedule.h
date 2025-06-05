#pragma once
#include <list>
#include <set>
#include <string>
#include "Lesson.h"

class Schedule {
private:
    std::string address;
    std::list<Lesson*> lessons;

public:
    Schedule(const std::string& address = "Unknown");
    ~Schedule();

    void addLesson(Lesson* lesson);
    void removeByTitle(const std::string& title);
    void findByDay(const std::string& day) const;
    void printAll() const;
    void printUniqueDays() const;
};
