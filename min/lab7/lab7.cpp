#include <iostream>
#include "Lecture.h"
#include "Pair.h"

int main() {
    std::cout << "=== Pair<int> ===\n";
    Pair<int> intPair(5, 5);
    intPair.print();
    std::cout << "Equal? " << (intPair.isEqual() ? "Yes" : "No") << "\n\n";

    std::cout << "=== Pair<std::string> ===\n";
    Pair<std::string> strPair("hello", "world");
    strPair.print();
    std::cout << "Equal? " << (strPair.isEqual() ? "Yes" : "No") << "\n\n";

    std::cout << "=== Pair<Lesson*> ===\n";
    Lecture* l1 = new Lecture("Math", "Monday", "10:00", "Dr. A");
    Lecture* l2 = new Lecture("Physics", "Tuesday", "12:00", "Dr. B");

    Pair<Lesson*> lessonPair(l1, l2);
    lessonPair.print();
    std::cout << "Equal? (pointers) " << (lessonPair.isEqual() ? "Yes" : "No") << "\n";

    delete l1;
    delete l2;

    return 0;
}
 