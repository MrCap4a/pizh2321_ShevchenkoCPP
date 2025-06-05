#include "Lecture.h"
#include <iostream>

Lecture::Lecture() : Lesson(), lecturer("Unknown") {}

Lecture::Lecture(const std::string& title, const std::string& day, const std::string& time, const std::string& lecturer)
    : Lesson(title, day, time), lecturer(lecturer) {
}

Lecture::~Lecture() {}

void Lecture::print() const {
    std::cout << "[Lecture] " << title << " | " << day << " | " << time
        << " | Lecturer: " << lecturer << "\n";
}

Lesson* Lecture::clone() const {
    return new Lecture(*this);
}
