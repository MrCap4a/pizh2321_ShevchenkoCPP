#include "Lesson.h"

Lesson::Lesson()
    : title("Unknown"), day("Unknown"), time("00:00") {
    std::cout << "Lesson: Default constructor\n";
}

Lesson::Lesson(const std::string& title, const std::string& day, const std::string& time)
    : title(title), day(day), time(time) {
    std::cout << "Lesson: Constructor with parameters\n";
}

Lesson::Lesson(const Lesson& other)
    : title(other.title), day(other.day), time(other.time) {
    std::cout << "Lesson: Copy constructor\n";
}

Lesson::~Lesson() {
    std::cout << "Lesson: Destructor\n";
}

void Lesson::print() const {
    std::cout << "[Lesson] " << title << " | " << day << " | " << time << "\n";
}

std::string Lesson::getTitle() const { return title; }
std::string Lesson::getDay() const { return day; }
std::string Lesson::getTime() const { return time; }
