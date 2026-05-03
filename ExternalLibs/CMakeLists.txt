cmake_minimum_required(VERSION 3.30..)

set(GLAD_SOURCES GLAD/include/glad/glad.h GLAD/src/glad.c)

add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC GLAD/include)

add_subdirectory(GLM)
add_subdirectory(GLFW)
add_subdirectory(SPDLOG)
add_subdirectory(Assimp)
