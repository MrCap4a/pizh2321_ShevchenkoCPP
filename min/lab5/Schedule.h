#pragma once
#include <vector>
#include <string>
#include "Lesson.h"

class Schedule {
private:
    std::string address;
    std::vector<Lesson*> lessons;

    static int lessonInScheduleCount;

public:
    Schedule(const std::string& address);
    ~Schedule();

    void addLesson(Lesson* lesson);
    void show() const;

    static int getScheduleSize(); // доступ к счётчику уроков в расписании
};
