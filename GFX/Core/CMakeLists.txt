cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_library(GFX_Core STATIC
        ${CORE_SOURCES}
        ${CORE_HEADERS}
)

target_include_directories(GFX_Core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include../../../../
)

target_link_libraries(GFX_Core
        PRIVATE
        spdlog::spdlog
        glad
        glm
        glfw
)

add_library(GFX::Core ALIAS GFX_Core)