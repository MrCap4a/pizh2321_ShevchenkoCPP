#include <iostream>
#include "Lecture.h"
#include "Schedule.h"

int main() {
    std::cout << "Initial Lesson count: " << Lesson::getCount() << "\n";
    std::cout << "Initial Schedule size: " << Schedule::getScheduleSize() << "\n";

    Schedule s("University Ave 5");

    s.addLesson(new Lecture("Math", "Mon", "09:00", "Dr. Smith"));
    s.addLesson(new Lecture("Physics", "Tue", "11:00", "Dr. Brown"));
    s.addLesson(new Lecture("Programming", "Wed", "13:00", "Prof. Lin"));

    std::cout << "\nLesson count after adding: " << Lesson::getCount() << "\n";
    std::cout << "Lessons in schedule: " << Schedule::getScheduleSize() << "\n";

    s.show();

    std::cout << "\n[Exiting main()]\n";
    return 0;
}
