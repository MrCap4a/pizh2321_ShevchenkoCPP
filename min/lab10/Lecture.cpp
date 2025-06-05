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

void Lecture::save(std::ofstream& out) const {
    out << "Lecture\n";
    out << title << '\n' << day << '\n' << time << '\n' << lecturer << '\n';
}

void Lecture::load(std::ifstream& in) {
    std::getline(in, title);
    std::getline(in, day);
    std::getline(in, time);
    std::getline(in, lecturer);
}
