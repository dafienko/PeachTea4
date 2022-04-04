#include "FileUtil.h"

#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <unordered_map>

using glm::ivec3;

void checkValidFile(const std::ifstream &file, const std::string& filename) {
    if (file.fail()) {
        std::cout << "Failed to open " << filename << std::endl;
        std::cin.get();
        exit(-1);
    }
}

std::vector<std::string> readFileLines(const std::string& filename) {
    std::ifstream infile(filename);
    checkValidFile(infile, filename);

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

void parseAndAppendVector(std::vector<float>& v, std::vector<std::string> elements, const int vectorSize) {
    for (int i = 1; i < vectorSize + 1; i++) {
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

ivec3 parseIndexGroup(std::string& indexGroupStr) {
    ivec3 res(-1, -1, -1);

    std::vector<std::string> elementComponents;
    str_split(indexGroupStr, '/', elementComponents);

    try {
        res.x = std::stoi(elementComponents.at(0)) - 1;
    } catch (std::invalid_argument &e) {
        std::cerr << "invalid index " << elementComponents.at(0) << std::endl;
    }

    if (elementComponents.size() > 1 && elementComponents.at(1).length() > 0) {
        try {
            res.y = std::stoi(elementComponents.at(1)) - 1;
        } catch (std::invalid_argument &e) {
            std::cerr << "invalid index " << elementComponents.at(1) << std::endl;
        }
    }

    if (elementComponents.size() > 2 && elementComponents.at(2).length() > 0) {
        try {
            res.z = std::stoi(elementComponents.at(2)) - 1;
        } catch (std::invalid_argument &e) {
            std::cerr << "invalid index " << elementComponents.at(2) << std::endl;
        }
    }

    return res;
}

void pushVecAtIndex(std::vector<float> &uiVec, std::vector<float> &objVec, int objIndex) {
    objIndex *= 3;
    uiVec.push_back(objVec.at(objIndex + 0));
    uiVec.push_back(objVec.at(objIndex + 1));
    uiVec.push_back(objVec.at(objIndex + 2));
}

void printObjData(int numIndices, int numVertices, int* indices, float* positions, float* normals, float* textureCoords) {
    std::cout << "obj: " << numIndices << " unique indices / " << numVertices << " vertices" << std::endl;

    std::cout << "vertex data:" << std::endl;
    for (int i = 0; i < numIndices; i++) {
        int vIndex = i * 3;
        std::cout << std::setprecision(2);
        std::cout << "\t" << i << ": ";
        std::cout << "p(" << *(positions + vIndex) << ", " << *(positions + vIndex + 1) << ", " << *(positions + vIndex + 2) << ") ";
        std::cout << "n(" << *(normals + vIndex) << ", " << *(normals + vIndex + 1) << ", " << *(normals + vIndex + 2) << ") ";
        std::cout << std::endl;
    }

    std::cout << std::endl << "indices:" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        if (i % 3 == 0) {
            std::cout << "\t";
        }
        std::cout << i << " ";
        if (i % 3 == 2) {
            std::cout << std::endl;
        }
    }
}

void loadObjFile(const std::string& filename, int &numIndices, int &numVertices, int* &indices, float* &positions, float* &normals, float* &textureCoords) {
    std::vector<float> positionsVector, normalsVector, textureVector;
    std::vector<float> uiPosVec, uiNormVec, uiTexVec;
    std::vector<int> uniqIndices;
    std::unordered_map<ivec3, int> uniqIndexTable;

    std::ifstream infile(filename);
    checkValidFile(infile, filename);

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
            parseAndAppendVector(positionsVector, elements, 3);
        } else if (elementType == "vn") {
            parseAndAppendVector(normalsVector, elements, 3);
        } else if (elementType == "vt") {
            parseAndAppendVector(textureVector, elements, 2);
        } else if (elementType == "f") {
            int faceVertexCount = std::min((int)elements.size() - 1, 4);
            int tmpIndices[4];
            int nUniqIndices = 0;

            for (int i = 1; i <= faceVertexCount; i++) {
                ivec3 indexGroup = parseIndexGroup(elements.at(i));
                std::cout << indexGroup.x << "/" << indexGroup.y << "/" << indexGroup.z << std::endl;

                if (uniqIndexTable.find(indexGroup) == uniqIndexTable.end()) {
                    std::cout << "unique\n";

                    pushVecAtIndex(uiPosVec, positionsVector, indexGroup.x);
                    if (indexGroup.z >= 0) {
                        pushVecAtIndex(uiNormVec, normalsVector, indexGroup.z);
                    }
                    if (indexGroup.y >= 0) {
                        pushVecAtIndex(uiTexVec, textureVector, indexGroup.y);
                    }
                    uniqIndexTable[indexGroup] = nUniqIndices++;
                } else {
                    std::cout << "reuse\n";
                }

                tmpIndices[i - 1] = uniqIndexTable[indexGroup];
            }

            if (faceVertexCount == 3) {
                uniqIndices.push_back(tmpIndices[0]);
                uniqIndices.push_back(tmpIndices[1]);
                uniqIndices.push_back(tmpIndices[2]);
            } else { // convert quad to two trinagles
                uniqIndices.push_back(tmpIndices[0]);
                uniqIndices.push_back(tmpIndices[1]);
                uniqIndices.push_back(tmpIndices[2]);

                uniqIndices.push_back(tmpIndices[2]);
                uniqIndices.push_back(tmpIndices[3]);
                uniqIndices.push_back(tmpIndices[0]);
            }
        }
    }

    indices = vecToArr(uniqIndices);
    positions = vecToArr(uiPosVec);
    normals = vecToArr(uiNormVec);
    textureCoords = vecToArr(uiTexVec);
    numVertices = (int)uniqIndices.size();
    numIndices = (int)uiPosVec.size() / 3;
}