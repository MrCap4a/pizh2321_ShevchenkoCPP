#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#ifdef _WIN32
  #include <direct.h>
#else
  #include <sys/stat.h>
#endif
#include "ParserTSV.h"
#include "Sand.h"
#include "BMPWriter.h"

static void makeDir(const std::string& path) {
#ifdef _WIN32
    _mkdir(path.c_str());
#else
    mkdir(path.c_str(), 0755);
#endif
}

int main(int argc, char* argv[]) {
    uint16_t width = 0, height = 0;
    std::string inputPath, outputPath;
    int maxIter = 100, freq = 0;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if ((a=="-w"||a=="--width") && i+1<argc)  width  = static_cast<uint16_t>(std::stoi(argv[++i]));
        else if ((a=="-l"||a=="--length")&& i+1<argc) height = static_cast<uint16_t>(std::stoi(argv[++i]));
        else if ((a=="-i"||a=="--input") && i+1<argc) inputPath  = argv[++i];
        else if ((a=="-o"||a=="--output")&& i+1<argc) outputPath = argv[++i];
        else if ((a=="-m"||a=="--max-iter")&& i+1<argc) maxIter = std::stoi(argv[++i]);
        else if ((a=="-f"||a=="--freq")&& i+1<argc)     freq    = std::stoi(argv[++i]);
    }

    if (width==0 || height==0 || inputPath.empty() || outputPath.empty()) {
        std::cerr << "Usage: --width <w> --length <h> --input <tsv> --output <dir> "
                  << "[--max-iter <n>] [--freq <f>]
";
        return 1;
    }

    makeDir(outputPath);
    auto grid = ParserTSV::parse(inputPath, width, height);
    Sand sand({width, height}, grid);

    for (int iter = 0; iter <= maxIter; ++iter) {
        if (freq > 0 && iter % freq == 0) {
            BMPWriter::saveBMP(outputPath + "/iter_" + std::to_string(iter) + ".bmp",
                               sand.getData());
        }
        if (iter == maxIter) break;
        auto before = sand.getData();
        sand.tick();
        if (sand.getData() == before) break;
    }
    if (freq == 0) {
        BMPWriter::saveBMP(outputPath + "/final.bmp", sand.getData());
    }
    return 0;
}
