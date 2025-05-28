#pragma once
#include <string>
#include <vector>
#include <iostream>

class Frame {
public:
    std::string id;
    uint32_t size;
    std::vector<char> data;

    Frame(const std::string& id, uint32_t size, const std::vector<char>& data);
    virtual void display() const;
    virtual ~Frame() = default;
};
