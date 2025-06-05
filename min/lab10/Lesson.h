#pragma once
#include <string>
#include <fstream>

class Lesson {
protected:
    std::string title;
    std::string day;
    std::string time;

public:
    Lesson();
    Lesson(const std::string& title, const std::string& day, const std::string& time);
    virtual ~Lesson();

    virtual void print() const = 0;
    virtual Lesson* clone() const = 0;

    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;

    std::string getTitle() const;
    std::string getDay() const;

};
