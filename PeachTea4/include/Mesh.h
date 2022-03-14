#ifndef PEACHTEAENVIRONMENT_MESH_H
#define PEACHTEAENVIRONMENT_MESH_H

#include "glad/glad.h"
#include "ShaderProgram.h"

namespace PT {
    class Mesh {
    private:
        GLuint vao, *vbos;
        float *vertices;
        float *colors;
        int numVertices;
    public:
        Mesh(int numVertices);
        Mesh(const std::string &filename);

        ~Mesh();

        void setVertices(glm::vec3 *vertices);

        void setColors(glm::vec4 *colors);

        void draw(glm::mat4x4 mvp);
    };
}

#endif //PEACHTEAENVIRONMENT_MESH_H
