#pragma once
#include <exception>
#include <string>

class IndexOutOfBoundsException : public std::exception {
private:
    std::string message;

public:
    IndexOutOfBoundsException(const std::string& msg) : message(msg) {}
    const char* what() const override {
        return message.c_str();
    }
};
