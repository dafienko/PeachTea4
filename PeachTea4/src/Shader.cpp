#include "glad/glad.h"
#include "Shader.h"
#include "FileUtil.h"
#include <iostream>
#include <memory>

Shader::Shader(const std::string filename, GLenum shaderType) {
    std::vector<std::string> lineStrings = readFileLines(filename);

    // convert string vector to char* vector
    char** lines = (char**)calloc(lineStrings.size(), sizeof(char*));
    for (int i = 0; i < lineStrings.size(); i++)
    {
        std::string lineString = lineStrings[i];
        int len = lineString.length();
        char* line = (char*)calloc(len + 1, sizeof(char));
        memset(line, 0, (len + 1) * sizeof(char));
        std::memcpy(line, lineString.c_str(), len * sizeof(char));
        lines[i] = line;
    }

    shader = glCreateShader(shaderType);
    glShaderSource(shader, lineStrings.size(), lines, NULL);
    glCompileShader(shader);

    for (int i = 0; i < lineStrings.size(); i++) {
        free(lines[i]);
    }
    free(lines);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(shader);

        std::cout << "Error compiling shader: " << filename << std::endl;
        std::cout << &errorLog[0] << std::endl;
        std::cin.get();
        exit(-1);
    }
}

GLuint Shader::getShader() {
    return shader;
}