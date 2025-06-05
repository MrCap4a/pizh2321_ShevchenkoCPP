#include <iostream>
#include <algorithm>
#include "Schedule.h"

int main() {
    Schedule schedule;

    // Добавляем лекции
    schedule.add(Lecture("Math", "Monday", "10:00", "Dr. Ivanov"));
    schedule.add(Lecture("History", "Wednesday", "12:00", "Ms. Petrova"));
    schedule.add(Lecture("Physics", "Monday", "14:00", "Dr. Ivanov"));
    schedule.add(Lecture("Literature", "Friday", "09:00", "Mr. Green"));

    std::cout << "== All lectures ==\n";
    schedule.printAll();

    // Сортировка по убыванию названия (лямбда в методе класса)
    std::cout << "\n== Sort by descending title ==\n";
    schedule.sortByTitleDescending();
    schedule.printAll();

    // Используем лямбду для отбора лекций по условию (в понедельник)
    auto mondayLectures = schedule.findAllByCondition([](const Lecture& lec) {
        return lec.getDay() == "Monday";
        });

    std::cout << "\n== Lectures on Monday (second container) ==\n";
    std::for_each(mondayLectures.begin(), mondayLectures.end(), [](const Lecture& lec) {
        lec.print();
        });

    // Сортировка обоих контейнеров по возрастанию
    schedule.sortByTitle();

    std::sort(mondayLectures.begin(), mondayLectures.end(), [](const Lecture& a, const Lecture& b) {
        return a < b;
        });

    std::cout << "\n== Sorted first container (ascending) ==\n";
    schedule.printAll();

    std::cout << "\n== Sorted second container (ascending) ==\n";
    std::for_each(mondayLectures.begin(), mondayLectures.end(), [](const Lecture& lec) {
        lec.print();
        });

    return 0;
}
