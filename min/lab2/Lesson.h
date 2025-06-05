#pragma once
#include <string>
#include <iostream>

class Lesson {
private:
    std::string title;
    std::string day;
    std::string time;

public:
    Lesson();
    Lesson(const std::string& title, const std::string& day, const std::string& time);
    Lesson(const Lesson& other);
    ~Lesson();

    void setTitle(const std::string& title);
    void setDay(const std::string& day);
    void setTime(const std::string& time);

    std::string getTitle() const;
    std::string getDay() const;
    std::string getTime() const;

    void setProperties();
    void setProperties(const std::string& title, const std::string& day, const std::string& time);
};
