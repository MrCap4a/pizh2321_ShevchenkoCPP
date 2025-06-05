#pragma once
#include "Lesson.h"

class LabWork : public Lesson {
private:
    std::string labRoom;

public:
    LabWork();
    LabWork(const std::string& title, const std::string& day, const std::string& time, const std::string& labRoom);
    ~LabWork();

    void print() const override;
};
