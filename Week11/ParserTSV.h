#ifndef PARSER_TSV_H
#define PARSER_TSV_H

#include <string>
#include <vector>
#include <cstdint>

class ParserTSV {
public:
    static std::vector<std::vector<uint64_t>>
    parse(const std::string& filename,
          uint16_t width,
          uint16_t height);
};

#endif // PARSER_TSV_H
