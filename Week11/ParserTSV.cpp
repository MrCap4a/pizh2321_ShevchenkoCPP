#include "ParserTSV.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<std::vector<uint64_t>>
ParserTSV::parse(const std::string& filename,
                 uint16_t width,
                 uint16_t height)
{
    std::vector<std::vector<uint64_t>> grid(
        width, std::vector<uint64_t>(height, 0)
    );

    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open TSV file: " + filename);
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string xs, ys, cs;
        if (!std::getline(ss, xs, '\t')) continue;
        if (!std::getline(ss, ys, '\t')) continue;
        if (!std::getline(ss, cs)) continue;
        uint16_t x = static_cast<uint16_t>(std::stoi(xs));
        uint16_t y = static_cast<uint16_t>(std::stoi(ys));
        uint64_t cnt = std::stoull(cs);
        if (x < width && y < height) {
            grid[x][y] = cnt;
        }
    }

    return grid;
}
