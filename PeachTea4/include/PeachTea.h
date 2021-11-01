//
// Created by Damien Afienko on 10/4/21.
//

#ifndef PEACHTEAENVIRONMENT_PEACHTEA_H
#define PEACHTEAENVIRONMENT_PEACHTEA_H

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "ext.hpp"

#include "FileUtil.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"

#include "lua.hpp"

namespace PT {
    extern ShaderProgram *meshShader;

    GLFWwindow *Init();
}

#endif //PEACHTEAENVIRONMENT_PEACHTEA_H
