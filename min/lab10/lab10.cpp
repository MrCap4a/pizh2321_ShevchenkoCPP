#include <iostream>
#include "Lecture.h"
#include "Schedule.h"

int main() {
    Schedule schedule("Tech Uni");

    schedule.addLesson(new Lecture("Math", "Monday", "10:00", "Dr. Ivanov"));
    schedule.addLesson(new Lecture("Physics", "Tuesday", "12:00", "Dr. Smith"));
    schedule.addLesson(new Lecture("English", "Monday", "14:00", "Ms. Brown"));
    schedule.addLesson(new Lecture("History", "Wednesday", "16:00", "Mr. Adams"));

    schedule.printAll();

    std::cout << "\n== Remove 'Physics' ==\n";
    schedule.removeByTitle("Physics");
    schedule.printAll();

    std::cout << "\n== Search by day 'Monday' ==\n";
    schedule.findByDay("Monday");

    std::cout << "\n== Unique days of the week ==\n";
    schedule.printUniqueDays();

    return 0;
}
