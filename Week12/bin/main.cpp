#include <iostream>
#include <string>
#include <vector>
#include "lib/ArgParser.h"

using namespace ArgumentParser;

int main() {
    // Имитация аргументов командной строки
    std::vector<std::string> args = {
        "program",          // argv[0]
        "--file", "config.txt",
        "--threads=4",
        "--verbose",
        "input1.txt",
        "input2.txt"
    };

    std::string fileName;
    int threadCount = 1;
    bool verbose = false;
    std::vector<std::string> inputFiles;

    ArgParser parser("Example: no console args");

    parser
        .AddHelp('h', "help", "Show help")
        .AddStringArgument('f', "file", "Input file")
        .Default("default.txt")
        .StoreValue(fileName)
        .AddIntArgument('t', "threads", "Number of threads")
        .Default(1)
        .StoreValue(threadCount)
        .AddFlag('v', "verbose", "Verbose mode")
        .StoreValue(verbose)
        .AddStringArgument("inputs", "Input files")
        .MultiValue()
        .Positional()
        .StoreValues(inputFiles);

    if (!parser.Parse(args)) {
        std::cerr << "Error: invalid arguments\n";
        return 1;
    }

    if (parser.Help()) {
        std::cout << parser.HelpDescription();
        return 0;
    }

    std::cout << "File: " << fileName << "\n";
    std::cout << "Threads: " << threadCount << "\n";
    std::cout << "Verbose: " << (verbose ? "on" : "off") << "\n";

    std::cout << "Input files:\n";
    for (const auto& f : inputFiles)
        std::cout << " - " << f << "\n";

    return 0;
}
