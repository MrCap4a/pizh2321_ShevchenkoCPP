#include "Lesson.h"
#include <iostream>

int Lesson::lessonCount = 0;

Lesson::Lesson()
    : title("Unknown"), day("Unknown"), time("00:00") {
    ++lessonCount;
    std::cout << "Lesson: Default constructor\n";
}

Lesson::Lesson(const std::string& title, const std::string& day, const std::string& time)
    : title(title), day(day), time(time) {
    ++lessonCount;
    std::cout << "Lesson: Constructor with parameters\n";
}

Lesson::~Lesson() {
    --lessonCount;
    std::cout << "Lesson: Destructor\n";
}

int Lesson::getCount() {
    return lessonCount;
}
