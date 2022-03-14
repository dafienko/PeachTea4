#ifndef PEACHTEAENVIRONMENT_FILEUTIL_H
#define PEACHTEAENVIRONMENT_FILEUTIL_H

#include <string>
#include <vector>

std::vector<std::string> readFileLines(const std::string &filename);
void loadObjFile(const std::string& filename, int &numVertices, float* &psitions, float* &normals, float* &colors);

#endif PEACHTEAENVIRONMENT_FILEUTIL_H
