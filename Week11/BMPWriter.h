#ifndef BMPWRITER_H
#define BMPWRITER_H

#include <string>
#include <vector>
#include <cstdint>

class BMPWriter {
public:
    static void saveBMP(const std::string& filename,
        const std::vector<std::vector<uint64_t>>& data);
};

#endif // BMPWRITER_H
