#include "Schedule.h"
#include <iostream>
#include "Lecture.h"

Schedule::Schedule(const std::string& address) : address(address) {}

Schedule::~Schedule() {
    for (Lesson* l : lessons)
        delete l;
}

void Schedule::addLesson(Lesson* lesson) {
    lessons.push_back(lesson);
}

void Schedule::removeByTitle(const std::string& title) {
    for (auto it = lessons.begin(); it != lessons.end(); ) {
        if ((*it)->getTitle() == title) {
            delete* it;
            it = lessons.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Schedule::findByDay(const std::string& day) const {
    std::cout << "Lessons for the day: " << day << "\n";
    for (const auto& l : lessons) {
        if (l->getDay() == day)
            l->print();
    }
}

void Schedule::printAll() const {
    std::cout << "\nFull schedule (" << address << "):\n";
    for (const auto& l : lessons)
        l->print();
}

void Schedule::printUniqueDays() const {
    std::set<std::string> days;
    for (const auto& l : lessons)
        days.insert(l->getDay());

    std::cout << "\nUnique days of classes:\n";
    for (const auto& d : days)
        std::cout << d << "\n";
}
