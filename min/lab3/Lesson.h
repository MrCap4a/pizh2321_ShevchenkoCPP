#pragma once
#include <string>
#include <iostream>

class Lesson {
protected:
    std::string title;
    std::string day;
    std::string time;

public:
    Lesson();
    Lesson(const std::string& title, const std::string& day, const std::string& time);
    Lesson(const Lesson& other);
    virtual ~Lesson();

    virtual void print() const;

    std::string getTitle() const;
    std::string getDay() const;
    std::string getTime() const;
};
