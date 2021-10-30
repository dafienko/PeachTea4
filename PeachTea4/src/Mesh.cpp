#include "PeachTea.h"

PT_Mesh::PT_Mesh(int numVertices) :
    numVertices(numVertices)
{
    glGenVertexArrays(1, &vao);

    vbos = (GLuint*)calloc(2, sizeof(GLuint));
    glGenBuffers(2, vbos);

    vertices = (vec3*)calloc(numVertices, sizeof(vec3));
    colors = (vec4*)calloc(numVertices, sizeof(vec4));
}

void PT_Mesh::setVertices(vec3* vertices) {
    for (int i = 0; i < numVertices; i++) {
        this->vertices[i][0] = vertices[i][0];
        this->vertices[i][1] = vertices[i][1];
        this->vertices[i][2] = vertices[i][2];
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vec3), this->vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(0);
}

void PT_Mesh::setColors(vec4* colors) {
    for (int i = 0; i < numVertices; i++) {
        this->colors[i][0] = colors[i][0];
        this->colors[i][1] = colors[i][1];
        this->colors[i][2] = colors[i][2];
        this->colors[i][3] = colors[i][3];
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vec4), this->colors, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(1);
}

void PT_Mesh::draw(mat4x4 mvp) {
    meshShader->bind();
    glBindVertexArray(vao);
    meshShader->setUniformMatrix("MVP", mvp);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

PT_Mesh::~PT_Mesh() {
    free(vertices);
    vertices = nullptr;

    free(colors);
    colors = nullptr;

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbos);
}