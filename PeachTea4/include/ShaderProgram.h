#ifndef PEACHTEAENVIRONMENT_SHADERPROGRAM_H
#define PEACHTEAENVIRONMENT_SHADERPROGRAM_H

#include <glad/glad.h>
#include "Shader.h"

class ShaderProgram{
private:
    GLuint program;
public:
    ShaderProgram(Shader vertexShader, Shader fragmentShader);
    void bind();
    const GLuint getProgram();
};

#endif //PEACHTEAENVIRONMENT_SHADERPROGRAM_H
