#include <iostream>
#include <vector>
#include "Lesson.h"
#include "Lecture.h"
#include "LabWork.h"

int main() {
    std::cout << "==== Step 1: Individual objects ====\n";

    Lesson* base = new Lesson("Math", "Monday", "10:00");
    Lecture* lec = new Lecture("Physics", "Tuesday", "12:00", "Dr. Brown");
    LabWork* lab = new LabWork("Programming", "Wednesday", "14:00", "Lab A");

    base->print();
    lec->print();
    lab->print();

    std::cout << "\n==== Step 2: Polymorphic array of base pointers ====\n";
    std::vector<Lesson*> schedule;
    schedule.push_back(base);
    schedule.push_back(lec);
    schedule.push_back(lab);

    for (Lesson* l : schedule) {
        l->print();
    }

    std::cout << "\n==== Step 3: Array of LabWorks ====\n";
    std::vector<LabWork> labs;
    labs.emplace_back("OS Lab", "Thursday", "16:00", "Lab B");
    labs.emplace_back("Networks", "Friday", "18:00", "Lab C");

    for (const auto& lw : labs) {
        lw.print();
    }

    std::cout << "\n==== Cleanup ====\n";
    for (Lesson* l : schedule) {
        delete l;
    }

    return 0;
}
