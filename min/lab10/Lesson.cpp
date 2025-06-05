#include "Lesson.h"

Lesson::Lesson() : title("Unknown"), day("Unknown"), time("00:00") {}

Lesson::Lesson(const std::string& title, const std::string& day, const std::string& time)
    : title(title), day(day), time(time) {
}

Lesson::~Lesson() {}

std::string Lesson::getTitle() const {
    return title;
}

std::string Lesson::getDay() const {
    return day;
}

