#include "BMPWriter.h"
#include <fstream>

struct RGB { uint8_t b, g, r; };

static RGB getColor(uint64_t grains) {
    if (grains == 0) return {255,255,255};
    if (grains == 1) return {0,255,0};
    if (grains == 2) return {255,0,255};
    if (grains == 3) return {0,255,255};
    return {0,0,0};
}

void BMPWriter::saveBMP(const std::string& filename,
    const std::vector<std::vector<uint64_t>>& data)
{
    int width  = static_cast<int>(data.size());
    int height = static_cast<int>(data[0].size());
    int rowBytes = (3 * width + 3) & ~3;
    int fileSize = 54 + rowBytes * height;

    std::vector<uint8_t> img(rowBytes * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RGB c = getColor(data[x][height-1-y]);
            int idx = y * rowBytes + x * 3;
            img[idx]   = c.b;
            img[idx+1] = c.g;
            img[idx+2] = c.r;
        }
    }

    uint8_t fileHeader[14] = {
        'B','M',
        static_cast<uint8_t>(fileSize),
        static_cast<uint8_t>(fileSize>>8),
        static_cast<uint8_t>(fileSize>>16),
        static_cast<uint8_t>(fileSize>>24),
        0,0,0,0,
        54,0,0,0
    };
    uint8_t infoHeader[40] = {
        40,0,0,0,
        static_cast<uint8_t>(width),
        static_cast<uint8_t>(width>>8),
        static_cast<uint8_t>(width>>16),
        static_cast<uint8_t>(width>>24),
        static_cast<uint8_t>(height),
        static_cast<uint8_t>(height>>8),
        static_cast<uint8_t>(height>>16),
        static_cast<uint8_t>(height>>24),
        1,0,24,0
    };

    std::ofstream out(filename, std::ios::binary);
    out.write(reinterpret_cast<char*>(fileHeader), 14);
    out.write(reinterpret_cast<char*>(infoHeader), 40);
    out.write(reinterpret_cast<char*>(img.data()), img.size());
}
