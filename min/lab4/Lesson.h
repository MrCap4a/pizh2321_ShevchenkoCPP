#pragma once
#include <string>

class Lesson {
protected:
    std::string title;
    std::string day;
    std::string time;

public:
    Lesson();
    Lesson(const std::string& title, const std::string& day, const std::string& time);
    virtual ~Lesson();

    std::string getTitle() const;
    std::string getDay() const;
    std::string getTime() const;

    virtual void print() const = 0;
};
