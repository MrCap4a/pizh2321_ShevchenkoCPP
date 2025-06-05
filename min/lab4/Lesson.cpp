#include "Lesson.h"
#include <iostream>

Lesson::Lesson()
    : title("Unknown"), day("Unknown"), time("00:00") {
    std::cout << "Lesson: Default constructor\n";
}

Lesson::Lesson(const std::string& title, const std::string& day, const std::string& time)
    : title(title), day(day), time(time) {
    std::cout << "Lesson: Constructor with parameters\n";
}

Lesson::~Lesson() {
    std::cout << "Lesson: Destructor\n";
}

std::string Lesson::getTitle() const { return title; }
std::string Lesson::getDay() const { return day; }
std::string Lesson::getTime() const { return time; }
