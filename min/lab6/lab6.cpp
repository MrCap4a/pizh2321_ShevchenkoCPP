#include <iostream>
#include "Schedule.h"
#include "Lecture.h"

int main() {
    Schedule schedule("Tech University");

    std::cout << "\n== Operator + ==\n";
    schedule + new Lecture("Math", "Monday", "10:00", "Dr. Brown");
    schedule + new Lecture("Physics", "Tuesday", "12:00", "Dr. Smith");

    std::cout << "\n== Operator ++ (prefix) ==\n";
    ++schedule;

    std::cout << "\n== Operator ++ (postfix) ==\n";
    schedule++;

    std::cout << "\n== Operator [] ==\n";
    Lesson* l = schedule[1];
    if (l) l->print();

    std::cout << "\n== Operator << ==\n";
    std::cout << schedule << "\n";

    std::cout << "\n== Full Schedule ==\n";
    schedule.show();

    return 0;
}
