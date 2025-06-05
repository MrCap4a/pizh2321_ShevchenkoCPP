#include <iostream>
#include "Lecture.h"
#include "Schedule.h"

int main() {
    Schedule schedule("Polytechnic");

    schedule.addLesson(new Lecture("Math", "Monday", "10:00", "Dr. Ivanov"));
    schedule.addLesson(new Lecture("CS", "Wednesday", "12:00", "Prof. Petrov"));

    std::cout << "\n== Original schedule ==\n";
    schedule.show();

    schedule.saveToFile("schedule.txt");

    Schedule loadedSchedule;
    loadedSchedule.loadFromFile("schedule.txt");

    std::cout << "\n== Loaded schedule ==\n";
    loadedSchedule.show();

    return 0;
}
