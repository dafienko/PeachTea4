#include "FileUtil.h"

#include <fstream>
#include <iostream>

std::vector<std::string> readFileLines(const std::string& filename) {
    std::vector<std::string> lines;

    std::ifstream infile(filename);
    if (infile.fail()) {
        std::cout << "Failed to open " << filename  << std::endl;
        std::cin.get();
        exit(-1);
    }

    std::string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line);
    }

    return lines;
}