#include <iostream>
#include "Schedule.h"

int main() {
    int id;
    std::string address;
    std::cout << "Enter institution ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter address: ";
    std::getline(std::cin, address);

    Schedule schedule(id, address);

    for (int i = 0; i < 2; ++i) {
        std::cout << "\nLesson " << i + 1 << " (manual input):\n";
        Lesson lesson;
        lesson.setProperties();
        schedule.addLesson(lesson);
    }

    for (int i = 2; i < 4; ++i) {
        std::string title, day, time;
        std::cout << "\nLesson " << i + 1 << " (with parameters):\n";
        std::cout << "Enter title: ";
        std::getline(std::cin, title);
        std::cout << "Enter day: ";
        std::getline(std::cin, day);
        std::cout << "Enter time: ";
        std::getline(std::cin, time);
        Lesson lesson(title, day, time);
        schedule.addLesson(lesson);
    }

    std::cout << "\nSchedule for institution #" << schedule.getInstitutionId()
        << " at address: " << schedule.getAddress() << "\n";

    const auto& lessons = schedule.getLessons();
    for (size_t i = 0; i < lessons.size(); ++i) {
        const Lesson& l = lessons[i];
        std::cout << i + 1 << ". " << l.getTitle() << " | " << l.getDay()
            << " | " << l.getTime() << "\n";
    }

    return 0;
}
