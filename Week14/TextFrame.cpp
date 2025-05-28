#include "TextFrame.h"

TextFrame::TextFrame(const std::string& id, uint32_t size, const std::vector<char>& data)
    : Frame(id, size, data) {
}

void TextFrame::display() const {
    std::cout << id << ": ";
    if (data.size() > 1) {
        for (size_t i = 1; i < data.size(); ++i) {
            if (isprint(static_cast<unsigned char>(data[i]))) std::cout << data[i];
        }
    }
    std::cout << std::endl;
}
