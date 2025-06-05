#include "Lecture.h"

Lecture::Lecture() : title("Unknown"), day("Unknown"), time("00:00"), lecturer("Unknown") {}

Lecture::Lecture(const std::string& title, const std::string& day, const std::string& time, const std::string& lecturer)
    : title(title), day(day), time(time), lecturer(lecturer) {
}

std::string Lecture::getTitle() const { return title; }
std::string Lecture::getDay() const { return day; }
std::string Lecture::getLecturer() const { return lecturer; }

void Lecture::print() const {
    std::cout << title << " | " << day << " | " << time << " | " << lecturer << "\n";
}

bool Lecture::operator<(const Lecture& other) const {
    return title < other.title; // сортировка по названию предмета
}
