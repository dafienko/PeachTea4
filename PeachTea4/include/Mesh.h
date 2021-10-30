#ifndef PEACHTEAENVIRONMENT_MESH_H
#define PEACHTEAENVIRONMENT_MESH_H

#include "glad/glad.h"
#include "linmath.h"
#include "ShaderProgram.h"

class PT_Mesh {
private:
    GLuint vao, *vbos;
    vec3* vertices;
    vec4* colors;
public:
    const int numVertices;
    PT_Mesh(int numVertices);
    ~PT_Mesh();

    void setVertices(vec3* vertices);
    void setColors(vec4* colors);

    void draw(mat4x4 mvp);
};

#endif //PEACHTEAENVIRONMENT_MESH_H
