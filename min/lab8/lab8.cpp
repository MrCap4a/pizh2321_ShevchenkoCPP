#include <iostream>
#include "Lecture.h"
#include "Schedule.h"
#include "IndexOutOfBoundsException.h"

int main() {
    Schedule schedule("Tech University");

    schedule.addLesson(new Lecture("Math", "Mon", "10:00", "Dr. Brown"));
    schedule.addLesson(new Lecture("Physics", "Tue", "12:00", "Dr. Smith"));

    schedule.show();

    try {
        std::cout << "\Attempt to access element at index 5...\n";
        Lesson* l = schedule[5]; // Ошибка
        l->print(); // не выполнится
    }
    catch (const IndexOutOfBoundsException& ex) {
        std::cerr << "Exception caught: " << ex.what() << "\n";
    }

    return 0;
}
