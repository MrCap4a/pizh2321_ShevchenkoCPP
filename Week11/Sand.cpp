#include "Sand.h"

Sand::Sand(const GridSize& s,
           const std::vector<std::vector<uint64_t>>& initData)
    : size(s), data(initData)
{}

void Sand::tick() {
    std::vector<std::vector<uint64_t>> buffer = data;
    for (uint16_t x = 0; x < size.width; ++x) {
        for (uint16_t y = 0; y < size.height; ++y) {
            if (data[x][y] > 3) {
                buffer[x][y] -= 4;
                if (y > 0)               buffer[x][y-1]++;
                if (y + 1 < size.height)buffer[x][y+1]++;
                if (x > 0)               buffer[x-1][y]++;
                if (x + 1 < size.width) buffer[x+1][y]++;
            }
        }
    }
    data.swap(buffer);
}

const std::vector<std::vector<uint64_t>>& Sand::getData() const {
    return data;
}
