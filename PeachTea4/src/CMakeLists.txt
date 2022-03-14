include_directories(
        ${PeachTeaEnvironment_SOURCE_DIR}/Sandbox/include
        ${PeachTeaEnvironment_SOURCE_DIR}/PeachTea4/include
        ${PeachTeaEnvironment_SOURCE_DIR}/glad/include
        ${PeachTeaEnvironment_SOURCE_DIR}/glfw-3.3.4/include
        ${PeachTeaEnvironment_SOURCE_DIR}/lua/include
        ${PeachTeaEnvironment_SOURCE_DIR}/glm/glm
        ${PeachTeaEnvironment_SOURCE_DIR}/stb
)
link_directories(
        ${PeachTeaEnvironment_SOURCE_DIR}/PeachTea4/src
        ${PeachTeaEnvironment_SOURCE_DIR}/glad/src
        ${PeachTeaEnvironment_SOURCE_DIR}/glm/glm
        ${PeachTeaEnvironment_SOURCE_DIR}/glfw-3.3.4/src
        ${PeachTeaEnvironment_SOURCE_DIR}/lua/src
        ${PeachTeaEnvironment_SOURCE_DIR}/lib
)
add_library(PeachTea4 PeachTea.cpp FileUtil.cpp Shader.cpp ShaderProgram.cpp Mesh.cpp)
target_link_libraries(PeachTea4 glad)
target_link_libraries(PeachTea4 glm)
target_link_libraries(PeachTea4 glfw)
target_link_libraries(PeachTea4 lua)
