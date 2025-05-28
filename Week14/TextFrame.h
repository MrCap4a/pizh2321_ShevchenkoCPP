#pragma once
#include "Frame.h"

class TextFrame : public Frame {
public:
    TextFrame(const std::string& id, uint32_t size, const std::vector<char>& data);
    void display() const override;
};
