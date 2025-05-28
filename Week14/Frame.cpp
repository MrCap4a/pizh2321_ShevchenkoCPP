#include "Frame.h"

Frame::Frame(const std::string& id, uint32_t size, const std::vector<char>& data)
    : id(id), size(size), data(data) {
}

void Frame::display() const {
    std::cout << id << ": ";
    for (char c : data) {
        if (isprint(static_cast<unsigned char>(c))) std::cout << c;
    }
    std::cout << std::endl;
}
