#include <iostream>
#include "Schedule.h"

int main() {
    std::cout << "==== Constructors Demo ====\n";

    Schedule s1;  // default
    Schedule s2(123, "University Ave 5");  // with params
    Schedule s3(s2);  // copy

    std::cout << "\n==== Lesson Constructors ====\n";

    Lesson l1;  // default
    Lesson l2("Math", "Monday", "10:00");  // with params
    Lesson l3(l2);  // copy

    std::cout << "\n==== Adding Lessons ====\n";

    s1.setInstitutionId(321);
    s1.setAddress("Tech Street 8");

    s1.addLessonWithParams("History", "Tuesday", "12:00");
    s1.addLessonCopies(l2, 3);

    std::cout << "\nSchedule for institution #" << s1.getInstitutionId()
        << " at address: " << s1.getAddress() << "\n";

    const auto& lessons = s1.getLessons();
    for (size_t i = 0; i < lessons.size(); ++i) {
        const Lesson& l = lessons[i];
        std::cout << i + 1 << ". " << l.getTitle() << " | " << l.getDay()
            << " | " << l.getTime() << "\n";
    }

    return 0;
}
