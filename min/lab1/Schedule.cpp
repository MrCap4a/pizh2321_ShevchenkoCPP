#include "Schedule.h"

Schedule::Schedule() : institutionId(0), address("Unknown") {}

Schedule::Schedule(int institutionId, const std::string& address)
    : institutionId(institutionId), address(address) {
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

int Schedule::getInstitutionId() const {
    return institutionId;
}

std::string Schedule::getAddress() const {
    return address;
}

const std::vector<Lesson>& Schedule::getLessons() const {
    return lessons;
}
