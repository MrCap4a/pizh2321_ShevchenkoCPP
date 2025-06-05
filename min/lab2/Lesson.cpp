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

void Lesson::setTitle(const std::string& title) { this->title = title; }
void Lesson::setDay(const std::string& day) { this->day = day; }
void Lesson::setTime(const std::string& time) { this->time = time; }

std::string Lesson::getTitle() const { return title; }
std::string Lesson::getDay() const { return day; }
std::string Lesson::getTime() const { return time; }

void Lesson::setProperties() {
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter day: ";
    std::getline(std::cin, day);
    std::cout << "Enter time: ";
    std::getline(std::cin, time);
}

void Lesson::setProperties(const std::string& title, const std::string& day, const std::string& time) {
    this->title = title;
    this->day = day;
    this->time = time;
}
