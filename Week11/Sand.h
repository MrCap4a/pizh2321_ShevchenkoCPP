#ifndef SAND_H
#define SAND_H

#include <vector>
#include <cstdint>

struct GridSize {
    uint16_t width;
    uint16_t height;
};

class Sand {
public:
    Sand(const GridSize& size,
         const std::vector<std::vector<uint64_t>>& initData);

    void tick();
    const std::vector<std::vector<uint64_t>>& getData() const;

private:
    GridSize size;
    std::vector<std::vector<uint64_t>> data;
};

#endif // SAND_H
