#include "Lecture.h"
#include <iostream>

Lecture::Lecture() : Lesson(), lecturer("Unknown") {
    std::cout << "Lecture: Default constructor\n";
}

Lecture::Lecture(const std::string& title, const std::string& day, const std::string& time, const std::string& lecturer)
    : Lesson(title, day, time), lecturer(lecturer) {
    std::cout << "Lecture: Constructor with parameters\n";
}

Lecture::~Lecture() {
    std::cout << "Lecture: Destructor\n";
}

void Lecture::print() const {
    std::cout << "[Lecture] " << title << " | " << day << " | " << time
        << " | Lecturer: " << lecturer << "\n";
}
