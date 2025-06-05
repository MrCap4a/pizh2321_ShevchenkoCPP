#pragma once
#include "Lesson.h"

class Lecture : public Lesson {
private:
    std::string lecturer;

public:
    Lecture();
    Lecture(const std::string& title, const std::string& day, const std::string& time, const std::string& lecturer);
    ~Lecture();

    void print() const override;
};
