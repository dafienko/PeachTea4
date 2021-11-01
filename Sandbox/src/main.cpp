#include <iostream>
#include "PeachTea.h"

glm::vec3 vertexPositions[] = {
    glm::vec3(-.6f, -.4f, 0.0f),
    glm::vec3(.6f, -.4f, 0.0f),
    glm::vec3(0.0f, 0.6f, 0.0f)
};

glm::vec4 vertexColors[] = {
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
};

int main()
{
    GLFWwindow* window = PT::Init();

    lua_State* L = luaL_newstate();
    luaopen_base(L);
    int r = luaL_dofile(L, "assets/scripts/test.lua");
    if (r == LUA_OK) {

    } else {
        std::string e = lua_tostring(L, -1);
        std::cerr << e << std::endl;
    }

    lua_close(L);

    PT::Mesh mesh(3);
    mesh.setVertices(vertexPositions);
    mesh.setColors(vertexColors);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glm::mat4x4 m(1.0);

        glfwGetFramebufferSize(window, &width, &height);
        float aspect = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);


        m = glm::translate(m, glm::vec3(0, 0, -2));
        m = glm::rotate(m, (float)glfwGetTime(), glm::vec3(0, 0, 1));
        glm::mat4x4 p = glm::perspective(glm::radians(70.0f), aspect, .1f, 100.0f);
        glm::mat4x4 mvp = p * m;

        mesh.draw(mvp);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
