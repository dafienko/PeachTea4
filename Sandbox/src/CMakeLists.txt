include_directories(
        ${PeachTeaEnvironment_SOURCE_DIR}/Sandbox/include
        ${PeachTeaEnvironment_SOURCE_DIR}/PeachTea4/include
        ${PeachTeaEnvironment_SOURCE_DIR}/glad/include
        ${PeachTeaEnvironment_SOURCE_DIR}/glfw-3.3.4/include
        ${PeachTeaEnvironment_SOURCE_DIR}/lua/include
        ${PeachTeaEnvironment_SOURCE_DIR}/glm/glm
)
link_directories(
        ${PeachTeaEnvironment_SOURCE_DIR}/PeachTea4/src
        ${PeachTeaEnvironment_SOURCE_DIR}/glad/src
        ${PeachTeaEnvironment_SOURCE_DIR}/glm/glm
        ${PeachTeaEnvironment_SOURCE_DIR}/glfw-3.3.4/src
        ${PeachTeaEnvironment_SOURCE_DIR}/lua/src
        ${PeachTeaEnvironment_SOURCE_DIR}/lib
)
add_executable(Sandbox main.cpp)
IF (WIN32)
    target_link_libraries(Sandbox C:/Windows/System32/gdi32.dll)
ENDIF()
target_link_libraries(Sandbox glad)
target_link_libraries(Sandbox glm)
target_link_libraries(Sandbox glfw)
target_link_libraries(Sandbox lua)
target_link_libraries(Sandbox PeachTea4)
