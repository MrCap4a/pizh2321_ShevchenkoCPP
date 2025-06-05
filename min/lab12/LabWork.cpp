#include "LabWork.h"
#include <iostream>

LabWork::LabWork() : Lesson(), labRoom("None") {
    std::cout << "LabWork: Default constructor\n";
}

LabWork::LabWork(const std::string& title, const std::string& day, const std::string& time, const std::string& labRoom)
    : Lesson(title, day, time), labRoom(labRoom) {
    std::cout << "LabWork: Constructor with parameters\n";
}

LabWork::~LabWork() {
    std::cout << "LabWork: Destructor\n";
}

void LabWork::print() const {
    std::cout << "[LabWork] " << title << " | " << day << " | " << time
        << " | Lab Room: " << labRoom << "\n";
}
