#include <iostream>
#include <algorithm>
#include "Schedule.h"

int main() {
    Schedule schedule;

    schedule.add(Lecture("Math", "Monday", "10:00", "Dr. Ivanov"));
    schedule.add(Lecture("History", "Wednesday", "12:00", "Ms. Petrova"));
    schedule.add(Lecture("Physics", "Monday", "14:00", "Dr. Ivanov"));
    schedule.add(Lecture("Literature", "Friday", "09:00", "Mr. Green"));

    std::cout << "== All lectures ==\n";
    schedule.printAll();

    // Сортировка по убыванию
    std::cout << "\n== Sorted by title (descending) ==\n";
    schedule.sortByTitleDescending();
    schedule.printAll();

    // Поиск лекций по условию (все лекции в понедельник)
    std::vector<Lecture> mondayLectures = schedule.findAllByCondition([](const Lecture& lec) {
        return lec.getDay() == "Monday";
        });

    std::cout << "\n== Lectures on Monday (moved to second container) ==\n";
    for (const auto& lec : mondayLectures) {
        lec.print();
    }

    schedule.sortByTitle();
    std::sort(mondayLectures.begin(), mondayLectures.end(), [](const Lecture& a, const Lecture& b) {
        return a < b;
        });

    std::cout << "\n== Sorted original container (ascending) ==\n";
    schedule.printAll();

    std::cout << "\n== Sorted Monday container (ascending) ==\n";
    for (const auto& lec : mondayLectures) {
        lec.print();
    }

    return 0;
}
