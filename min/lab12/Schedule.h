#pragma once
#include <vector>
#include <functional>
#include "Lecture.h"

class Schedule {
private:
    std::vector<Lecture> lectures;

public:
    void add(const Lecture& lec);
    void sortByTitle();
    void sortByTitleDescending();
    int countByLecturer(const std::string& name) const;
    const Lecture* findByDay(const std::string& day) const;
    std::vector<Lecture> findAllByCondition(std::function<bool(const Lecture&)> predicate) const;
    void printAll() const;
    const std::vector<Lecture>& getLectures() const;
    void setLectures(const std::vector<Lecture>& newLectures);
};
