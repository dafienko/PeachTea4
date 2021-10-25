#ifndef PEACHTEAENVIRONMENT_SHADER_H
#define PEACHTEAENVIRONMENT_SHADER_H

#include <string>

class Shader{
private:
    GLuint shader;
public:
    Shader(const std::string filename, GLenum shaderType);
    GLuint getShader();
};


#endif //PEACHTEAENVIRONMENT_SHADER_H
