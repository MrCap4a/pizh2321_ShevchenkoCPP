#pragma once
#include <string>
#include <iostream>

class Lecture {
private:
    std::string title;
    std::string day;
    std::string time;
    std::string lecturer;

public:
    Lecture();
    Lecture(const std::string& title, const std::string& day, const std::string& time, const std::string& lecturer);

    std::string getTitle() const;
    std::string getDay() const;
    std::string getLecturer() const;

    void print() const;

    // Для сортировки по title
    bool operator<(const Lecture& other) const;
};
