#include "number.h"
#include <iostream>

int main() {
    // Создание чисел из uint32_t
    uint2022_t a = from_uint(123456789);
    uint2022_t b = from_uint(987654321);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    // Сложение
    uint2022_t sum = a + b;
    std::cout << "a + b = " << sum << std::endl;

    // Вычитание
    uint2022_t diff = b - a;
    std::cout << "b - a = " << diff << std::endl;

    // Умножение
    uint2022_t product = a * b;
    std::cout << "a * b = " << product << std::endl;

    // Деление (если реализовано)
    uint2022_t quotient = b / a;
    std::cout << "b / a = " << quotient << std::endl;

    // Сравнение
    std::cout << "a == b? " << (a == b ? "yes" : "no") << std::endl;
    std::cout << "a < b? " << (a < b ? "yes" : "no") << std::endl;

    // Создание из строки
    uint2022_t c = from_string("123456789012345678901234567890");
    std::cout << "c = " << c << std::endl;

    return 0;
}
