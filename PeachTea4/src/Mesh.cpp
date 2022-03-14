#include "PeachTea.h"

namespace PT {
    Mesh::Mesh(int numVertices) : numVertices(numVertices)
    {
        glGenVertexArrays(1, &vao);

        vbos = (GLuint *) calloc(2, sizeof(GLuint));
        glGenBuffers(2, vbos);

        vertices = (float *) calloc(numVertices, sizeof(float) * 3);
        colors = (float *) calloc(numVertices, sizeof(float) * 4);
    }

    Mesh::Mesh(const std::string &filename) {
        glGenVertexArrays(1, &vao);

        vbos = (GLuint *) calloc(2, sizeof(GLuint));
        glGenBuffers(2, vbos);

        float* normals;
        loadObjFile(filename, numVertices, vertices, normals, colors);
    }

    void Mesh::setVertices(glm::vec3 *vertices) {
        for (int i = 0; i < numVertices; i++) {
            this->vertices[i * 3 + 0] = vertices[i].x;
            this->vertices[i * 3 + 1] = vertices[i].y;
            this->vertices[i * 3 + 2] = vertices[i].z;
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float) * 3, this->vertices, GL_STATIC_DRAW);

        glBindVertexArray(vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) (0));
        glEnableVertexAttribArray(0);
    }

    void Mesh::setColors(glm::vec4 *colors) {
        for (int i = 0; i < numVertices; i++) {
            this->colors[i * 4 + 0] = colors[i].x;
            this->colors[i * 4 + 1] = colors[i].y;
            this->colors[i * 4 + 2] = colors[i].z;
            this->colors[i * 4 + 3] = colors[i].w;
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float) * 4, this->colors, GL_STATIC_DRAW);

        glBindVertexArray(vao);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *) (0));
        glEnableVertexAttribArray(1);
    }

    void Mesh::draw(glm::mat4x4 mvp) {
        meshShader->bind();
        glBindVertexArray(vao);
        meshShader->setUniformMatrix("MVP", mvp);
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
    }

    Mesh::~Mesh() {
        free(vertices);
        vertices = nullptr;

        free(colors);
        colors = nullptr;

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(2, vbos);
    }
}