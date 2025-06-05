#include "Schedule.h"
#include "Lecture.h"
#include <iostream>

Schedule::Schedule(const std::string& address) : address(address) {}

Schedule::~Schedule() {
    for (Lesson* l : lessons)
        delete l;
}

void Schedule::addLesson(Lesson* lesson) {
    lessons.push_back(lesson);
}

void Schedule::show() const {
    std::cout << "\nSchedule at " << address << ":\n";
    for (Lesson* l : lessons)
        l->print();
}

void Schedule::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Не удалось открыть файл для записи\n";
        return;
    }

    out << address << '\n';
    out << lessons.size() << '\n';
    for (Lesson* l : lessons)
        l->save(out);
}

void Schedule::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Не удалось открыть файл для чтения\n";
        return;
    }

    for (Lesson* l : lessons) delete l;
    lessons.clear();

    std::getline(in, address);
    size_t count;
    in >> count;
    in.ignore(); // убрать \n после числа

    for (size_t i = 0; i < count; ++i) {
        std::string type;
        std::getline(in, type);

        Lesson* l = nullptr;
        if (type == "Lecture") l = new Lecture();
        else continue; // если неизвестный тип — пропустить

        l->load(in);
        lessons.push_back(l);
    }
}
