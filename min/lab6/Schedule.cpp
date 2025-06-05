#include "Schedule.h"
#include "Lecture.h"
#include <iostream>

Schedule::Schedule(const std::string& address) : address(address) {}

Schedule::Schedule(const Schedule& other) : address(other.address) {
    for (Lesson* l : other.lessons)
        lessons.push_back(l->clone());
}

Schedule& Schedule::operator=(const Schedule& other) {
    if (this == &other) return *this;

    for (Lesson* l : lessons) delete l;
    lessons.clear();

    address = other.address;
    for (Lesson* l : other.lessons)
        lessons.push_back(l->clone());

    return *this;
}

Schedule::~Schedule() {
    for (Lesson* l : lessons)
        delete l;
}

void Schedule::addLesson(Lesson* lesson) {
    lessons.push_back(lesson);
}

void Schedule::show() const {
    std::cout << "\nSchedule at " << address << ":\n";
    for (Lesson* l : lessons)
        l->print();
}

Schedule& Schedule::operator+(Lesson* lesson) {
    this->addLesson(lesson->clone());
    return *this;
}

Schedule& Schedule::operator++() {
    this->addLesson(new Lecture("Default Lecture", "Monday", "09:00", "Default Teacher"));
    return *this;
}

Schedule& Schedule::operator++(int) {
    this->addLesson(new Lecture("Default Lecture", "Monday", "09:00", "Default Teacher"));
    return *this;
}

Lesson* Schedule::operator[](size_t index) {
    if (index < lessons.size()) return lessons[index];
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Schedule& s) {
    os << "Schedule at " << s.address << ", " << s.lessons.size() << " lessons total.";
    return os;
}
