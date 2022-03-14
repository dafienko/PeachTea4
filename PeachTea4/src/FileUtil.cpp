#include "FileUtil.h"
#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::ifstream open_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (infile.fail()) {
        std::cout << "Failed to open " << filename  << std::endl;
        std::cin.get();
        exit(-1);
    }

    return infile;
}

std::vector<std::string> readFileLines(const std::string& filename) {
    std::ifstream infile = open_file(filename);
    std::vector<std::string> lines;

    std::string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line + "\n");
    }

    return lines;
}

void str_split(const std::string &str, char delim, std::vector<std::string> &elements) {
    std::stringstream ss(str);

    std::string element;
    while (std::getline(ss, element, delim)) {
        elements.push_back(element);
    }
}

void parseAndAppendVector(std::vector<float> v, std::vector<std::string> elements) {
    for (int i = 1; i < 4; i++) {
        float f = 0.0f;

        try {
            f = std::stof(elements.at(i));
        } catch (std::invalid_argument &e) {
            std::cerr << "invalid position component " << elements.at(i) << std::endl;
        }

        v.push_back(f);
    }
}

template <typename T>
T* vecToArr(std::vector<T> v) {
    T* ptr = (T*)calloc(v.size(), sizeof(T));
    std::copy(v.begin(), v.end(), ptr);
    return ptr;
}

void loadObjFile(const std::string& filename, int &numIndices, int* &indices, float* &positions, float* &normals, float* &colors) {
    std::vector<float> positionsVector, normalsVector, colorsVector;
    std::vector<int> indicesVector;

    std::ifstream infile = open_file(filename);
    std::string line;
    while(std::getline(infile, line)) {
        // don't process comments
        std::size_t commentIndex = line.find('#');
        if (commentIndex != std::string::npos) {
            line = line.substr(0, commentIndex);
        }

        std::vector<std::string> elements;
        str_split(line, ' ', elements);

        if (elements.size() < 4) {
            continue;
        }

        std::string elementType = elements.at(0);
        if (elementType == "v") {
            parseAndAppendVector(positionsVector, elements);
        } else if (elementType == "vn") {
            parseAndAppendVector(normalsVector, elements);
        } else if (elementType == "vt") {
            parseAndAppendVector(colorsVector, elements);
        } else if (elementType == "f") {
            int numFaces = std::min((int)elements.size() - 1, 4);
            int tmpIndices[4];
            for (int i = 1; i < numFaces; i++) {
                std::vector<std::string> elementComponents;
                str_split(elements.at(i), '/', elementComponents);
                int index = 0;
                try {
                    i = std::stoi(elementComponents.at(0));
                } catch (std::invalid_argument &e) {
                    std::cerr << "invalid index " << elementComponents.at(0) << std::endl;
                }
                tmpIndices[i - 1] = index;
            }

            if (numFaces == 3) {
                indicesVector.push_back(tmpIndices[0]);
                indicesVector.push_back(tmpIndices[1]);
                indicesVector.push_back(tmpIndices[2]);
            } else { // convert quad to two trinagles
                indicesVector.push_back(tmpIndices[0]);
                indicesVector.push_back(tmpIndices[1]);
                indicesVector.push_back(tmpIndices[2]);

                indicesVector.push_back(tmpIndices[2]);
                indicesVector.push_back(tmpIndices[3]);
                indicesVector.push_back(tmpIndices[0]);
            }
        }
    }

    indices = vecToArr(indicesVector);
    positions = vecToArr(positionsVector);
    normals = vecToArr(normalsVector);
    colors = vecToArr(colorsVector);
    numIndices = (int)indicesVector.size();
}