#include "PeachTea.h"

vec3 vertexPositions[] = {
    {-.6f, -.4f, 0.0f},
    {.6f, -.4f, 0.0f},
    {0.0f, 0.6f, 0.0f}
};

vec4 vertexColors[] = {
    {1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
};

int main()
{
    GLFWwindow* window = PT_Init();

    PT_Mesh mesh(3);
    mesh.setVertices(vertexPositions);
    mesh.setColors(vertexColors);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        mesh.draw(mvp);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
