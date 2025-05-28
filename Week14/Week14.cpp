#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <cstring>
#include "Frame.h"
#include "TextFrame.h"



std::unique_ptr<Frame> create_frame(const std::string& id, uint32_t size, const std::vector<char>& data) {
    if (id[0] == 'T') return std::make_unique<TextFrame>(id, size, data);
    return std::make_unique<Frame>(id, size, data);
}

uint32_t syncsafe_to_int(const char bytes[4]) {
    return (bytes[0] & 0x7F) << 21 |
        (bytes[1] & 0x7F) << 14 |
        (bytes[2] & 0x7F) << 7 |
        (bytes[3] & 0x7F);
}

void parse_id3v2(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file!\n";
        return;
    }

    char header[10];
    file.read(header, 10);
    if (std::strncmp(header, "ID3", 3) != 0 || header[3] != 4) {
        std::cerr << "Not a valid ID3v2.4 file.\n";
        return;
    }

    uint32_t tag_size = syncsafe_to_int(header + 6);
    size_t bytes_read = 0;

    while (bytes_read < tag_size) {
        char frame_header[10];
        file.read(frame_header, 10);
        if (file.gcount() < 10 || frame_header[0] == 0) break;

        std::string frame_id(frame_header, frame_header + 4);
        uint32_t frame_size = (unsigned char)frame_header[4] << 24 |
            (unsigned char)frame_header[5] << 16 |
            (unsigned char)frame_header[6] << 8 |
            (unsigned char)frame_header[7];

        std::vector<char> frame_data(frame_size);
        file.read(frame_data.data(), frame_size);

        auto frame = create_frame(frame_id, frame_size, frame_data);
        frame->display();

        bytes_read += 10 + frame_size;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.mp3>\n";
        return 1;
    }

    parse_id3v2(argv[1]);
    return 0;
}
