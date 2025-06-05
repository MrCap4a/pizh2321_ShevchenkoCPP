#include "Schedule.h"
#include <iostream>

int Schedule::lessonInScheduleCount = 0;

Schedule::Schedule(const std::string& address) : address(address) {
    std::cout << "Schedule: Constructor\n";
}

Schedule::~Schedule() {
    for (Lesson* l : lessons) {
        delete l;
    }
    std::cout << "Schedule: Destructor\n";
}

void Schedule::addLesson(Lesson* lesson) {
    lessons.push_back(lesson);
    ++lessonInScheduleCount;
}

void Schedule::show() const {
    std::cout << "\nSchedule at " << address << ":\n";
    for (const Lesson* l : lessons) {
        l->print();
    }
}

int Schedule::getScheduleSize() {
    return lessonInScheduleCount;
}
