#pragma once
#include <string>

class Lesson {
protected:
    std::string title;
    std::string day;
    std::string time;

private:
    static int lessonCount;

public:
    Lesson();
    Lesson(const std::string& title, const std::string& day, const std::string& time);
    virtual ~Lesson();

    static int getCount(); // доступ к счётчику

    virtual void print() const = 0;
};
