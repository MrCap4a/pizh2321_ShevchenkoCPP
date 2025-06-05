#include <iostream>
#include "Lecture.h"
#include "LabWork.h"
#include "Schedule.h"

int main() {
    std::cout << "==== Step 1: Polymorphic array ====\n";
    Lesson* lessons[3];
    lessons[0] = new Lecture("Physics", "Monday", "10:00", "Dr. Brown");
    lessons[1] = new LabWork("Programming", "Tuesday", "12:00", "Lab A");
    lessons[2] = new Lecture("Math", "Wednesday", "14:00", "Dr. Smith");

    for (int i = 0; i < 3; ++i) {
        lessons[i]->print();
    }

    std::cout << "\n==== Step 2: Schedule container ====\n";
    Schedule schedule("University Ave 5");
    for (int i = 0; i < 3; ++i) {
        schedule.addLesson(lessons[i]);
    }

    schedule.show();

    return 0;
}
