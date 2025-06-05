#include "Schedule.h"
#include <iostream>

Schedule::Schedule() : institutionId(0), address("Unknown") {
    std::cout << "Schedule: Default constructor\n";
}

Schedule::Schedule(int institutionId, const std::string& address)
    : institutionId(institutionId), address(address) {
    std::cout << "Schedule: Constructor with parameters\n";
}

Schedule::Schedule(const Schedule& other)
    : institutionId(other.institutionId), address(other.address), lessons(other.lessons) {
    std::cout << "Schedule: Copy constructor\n";
}

Schedule::~Schedule() {
    std::cout << "Schedule: Destructor\n";
}

void Schedule::setInstitutionId(int id) {
    institutionId = id;
}

void Schedule::setAddress(const std::string& address) {
    this->address = address;
}

void Schedule::addLesson(const Lesson& lesson) {
    lessons.push_back(lesson);
}

void Schedule::addLessonWithParams(const std::string& title, const std::string& day, const std::string& time) {
    Lesson lesson(title, day, time);
    lessons.push_back(lesson);
}

void Schedule::addLessonCopies(const Lesson& lesson, int count) {
    for (int i = 0; i < count; ++i) {
        Lesson copy(lesson);
        lessons.push_back(copy);
    }
}

int Schedule::getInstitutionId() const {
    return institutionId;
}

std::string Schedule::getAddress() const {
    return address;
}

const std::vector<Lesson>& Schedule::getLessons() const {
    return lessons;
}
