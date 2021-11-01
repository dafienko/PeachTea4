#include "ShaderProgram.h"
#include <vector>
#include <iostream>

namespace PT {
    ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader) {
        program = glCreateProgram();
        glAttachShader(program, vertexShader.getShader());
        glAttachShader(program, fragmentShader.getShader());
        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            glDeleteShader(vertexShader.getShader());
            glDeleteShader(fragmentShader.getShader());

            std::cout << "Error compiling shader program " << std::endl;
            std::cout << &infoLog[0] << std::endl;
            std::cin.get();
            exit(-1);
        }

        glDetachShader(program, vertexShader.getShader());
        glDetachShader(program, fragmentShader.getShader());
    }

    void ShaderProgram::bind() {
        glUseProgram(program);
    }

    GLint ShaderProgram::getUniform(const std::string &uniformName) {
        return glGetUniformLocation(getProgram(), uniformName.c_str());
    }

    void ShaderProgram::setUniformMatrix(const std::string &uniformName, glm::mat4x4 value) {
        glUniformMatrix4fv(getUniform(uniformName), 1, GL_FALSE, glm::value_ptr(value));
    }

    GLuint ShaderProgram::getProgram() {
        return program;
    }
}