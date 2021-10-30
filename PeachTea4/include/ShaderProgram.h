#ifndef PEACHTEAENVIRONMENT_SHADERPROGRAM_H
#define PEACHTEAENVIRONMENT_SHADERPROGRAM_H

#include <glad/glad.h>
#include "Shader.h"
#include "linmath.h"


class ShaderProgram{
private:
    GLuint program;
public:
    ShaderProgram(Shader vertexShader, Shader fragmentShader);

    GLint getUniform(const std::string& uniformName);
    void setUniformMatrix(const std::string& uniformName, mat4x4 value);

    void bind();

    GLuint getProgram();
};

#endif //PEACHTEAENVIRONMENT_SHADERPROGRAM_H
