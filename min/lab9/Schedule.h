#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Lesson.h"

class Schedule {
private:
    std::string address;
    std::vector<Lesson*> lessons;

public:
    Schedule(const std::string& address = "Unknown");
    ~Schedule();

    void addLesson(Lesson* lesson);
    void show() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
