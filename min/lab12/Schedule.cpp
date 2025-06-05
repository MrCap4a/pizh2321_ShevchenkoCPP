#include "Schedule.h"
#include <algorithm>
#include <iostream>

void Schedule::add(const Lecture& lec) {
    lectures.push_back(lec);
}

void Schedule::sortByTitle() {
    std::sort(lectures.begin(), lectures.end());
}

void Schedule::sortByTitleDescending() {
    std::sort(lectures.begin(), lectures.end(), [](const Lecture& a, const Lecture& b) {
        return b < a;
        });
}

int Schedule::countByLecturer(const std::string& name) const {
    return static_cast<int>(std::count_if(lectures.begin(), lectures.end(),
        [&name](const Lecture& l) {
            return l.getLecturer() == name;
        }));
}

const Lecture* Schedule::findByDay(const std::string& day) const {
    auto it = std::find_if(lectures.begin(), lectures.end(),
        [&day](const Lecture& l) {
            return l.getDay() == day;
        });

    if (it != lectures.end())
        return &(*it);
    return nullptr;
}

std::vector<Lecture> Schedule::findAllByCondition(std::function<bool(const Lecture&)> predicate) const {
    std::vector<Lecture> result;
    for (const auto& lec : lectures) {
        if (predicate(lec)) {
            result.push_back(lec);
        }
    }
    return result;
}

const std::vector<Lecture>& Schedule::getLectures() const {
    return lectures;
}

void Schedule::setLectures(const std::vector<Lecture>& newLectures) {
    lectures = newLectures;
}

void Schedule::printAll() const {
    std::for_each(lectures.begin(), lectures.end(),
        [](const Lecture& l) { l.print(); });
}
