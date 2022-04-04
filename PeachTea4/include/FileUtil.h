#ifndef PEACHTEAENVIRONMENT_FILEUTIL_H
#define PEACHTEAENVIRONMENT_FILEUTIL_H

#include <string>
#include <vector>

std::vector<std::string> readFileLines(const std::string &filename);
void loadObjFile(const std::string& filename, int &numIndices, int &numVertices, int* &indices, float* &positions, float* &normals, float* &textureCoords);

void printObjData(int numIndices, int numVertices, int* indices, float* positions, float* normals, float* textureCoords);

#endif PEACHTEAENVIRONMENT_FILEUTIL_H
