#include <iostream>
#include <chrono>
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


lua_State* L;

lua_State* init_lua() {
    L = luaL_newstate();
    luaopen_base(L);
    int r = luaL_dofile(L, "assets/scripts/test.lua");
    if (r != LUA_OK) {
        std::string e = lua_tostring(L, -1);
        std::cerr << e << std::endl;
    }

    return L;
}

void destroy_lua() {
    lua_close(L);
}

std::chrono::milliseconds programStart;
std::chrono::milliseconds get_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
    );
}

float get_time() {
    std::chrono::milliseconds dt_ms = get_ms() - programStart;

    return dt_ms.count() / 1000.0f;
}

float lastUpdate = 0.0f, lastRender = 0.0f;

void call_lua_update() {
    float now = get_time();

    lua_getglobal(L, "OnUpdate");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, now - lastUpdate);
        lua_pcall(L, 1, 0, 0);
    }

    lastUpdate = now;
}

void call_lua_render() {
    float now = get_time();

    lua_getglobal(L, "OnRender");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, now - lastRender);
        lua_pcall(L, 1, 0, 0);
    }

    lastRender = now;
}

PT::Mesh* mesh;
GLFWwindow* window;

int width = 0, height = 0;

void render() {
    call_lua_render();

    glClear(GL_COLOR_BUFFER_BIT);

    float aspect = width / (float) height;
    glm::mat4x4 m(1.0);
    m = glm::translate(m, glm::vec3(0, 0, -2));
    m = glm::rotate(m, (float)glfwGetTime(), glm::vec3(0, 0, 1));
    glm::mat4x4 p = glm::perspective(glm::radians(70.0f), aspect, .1f, 100.0f);
    glm::mat4x4 mvp = p * m;

    mesh->draw(mvp);

    glfwSwapBuffers(window);
}

void update() {
    call_lua_update();
}

void resize() {
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void framebuffer_size_callback(GLFWwindow* win, int w, int h)
{
    resize();
    render();
}

int main()
{
    programStart = get_ms();
    window = PT::Init();

    init_lua();

    ///*
    mesh = new PT::Mesh(3);
    mesh->setVertices(vertexPositions);
    mesh->setColors(vertexColors);
    //*/
    float *positions, *normals, *textureCoords;
    int numIndices, numVertices, *indices;
    loadObjFile("assets/models/square.obj", numIndices, numVertices, indices, positions, normals, textureCoords);
    printObjData(numIndices, numVertices, indices, positions, normals, textureCoords);

    resize();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        update();
        render();

        glfwPollEvents();
    }

    destroy_lua();

    glfwDestroyWindow(window);

    glfwTerminate();
}
