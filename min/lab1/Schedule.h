#pragma once
#include <string>
#include <vector>
#include "Lesson.h"

class Schedule {
private:
    int institutionId;
    std::string address;
    std::vector<Lesson> lessons;

public:
    Schedule();
    Schedule(int institutionId, const std::string& address);

    void setInstitutionId(int id);
    void setAddress(const std::string& address);
    void addLesson(const Lesson& lesson);

    int getInstitutionId() const;
    std::string getAddress() const;
    const std::vector<Lesson>& getLessons() const;
};
