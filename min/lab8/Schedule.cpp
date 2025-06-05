#include "Schedule.h"
#include <iostream>

Schedule::Schedule(const std::string& address) : address(address) {}

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

Lesson* Schedule::operator[](size_t index) {
    if (index >= lessons.size()) {
        throw IndexOutOfBoundsException("Error: index " + std::to_string(index) + " out of range!");
    }
    return lessons[index];
}

std::ostream& operator<<(std::ostream& os, const Schedule& s) {
    os << "Schedule at " << s.address << ", " << s.lessons.size() << " lessons total.";
    return os;
}
