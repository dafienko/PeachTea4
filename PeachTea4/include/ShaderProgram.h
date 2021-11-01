#ifndef PEACHTEAENVIRONMENT_SHADERPROGRAM_H
#define PEACHTEAENVIRONMENT_SHADERPROGRAM_H

#include <glad/glad.h>
#include "Shader.h"
#include "ext.hpp"

namespace PT {
    class ShaderProgram {
    private:
        GLuint program;
    public:
        ShaderProgram(Shader vertexShader, Shader fragmentShader);

        GLint getUniform(const std::string &uniformName);

        void setUniformMatrix(const std::string &uniformName, glm::mat4x4 value);

        void bind();

        GLuint getProgram();
    };
}

#endif //PEACHTEAENVIRONMENT_SHADERPROGRAM_H
