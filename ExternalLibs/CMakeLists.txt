cmake_minimum_required(VERSION 3.30..)

set(GLAD_SOURCES GLAD/include/glad/glad.h GLAD/src/glad.c)

add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC GLAD/include)

add_subdirectory(GLM)
add_subdirectory(GLFW)
add_subdirectory(SPDLOG)
add_subdirectory(Assimp)
add_subdirectory(FreeType)

if(MINGW AND TARGET assimp)
    get_target_property(ASSIMP_LINK_LIBRARIES assimp LINK_LIBRARIES)
    if(ASSIMP_LINK_LIBRARIES)
        list(REMOVE_ITEM ASSIMP_LINK_LIBRARIES
                -static-libgcc
                -static-libstdc++
                -Wl,-Bstatic
                -lstdc++)
        set_target_properties(assimp PROPERTIES LINK_LIBRARIES "${ASSIMP_LINK_LIBRARIES}")
    endif()

    get_target_property(ASSIMP_INTERFACE_LINK_LIBRARIES assimp INTERFACE_LINK_LIBRARIES)
    if(ASSIMP_INTERFACE_LINK_LIBRARIES)
        list(REMOVE_ITEM ASSIMP_INTERFACE_LINK_LIBRARIES
                -static-libgcc
                -static-libstdc++
                -Wl,-Bstatic
                -lstdc++)
        set_target_properties(assimp PROPERTIES
                INTERFACE_LINK_LIBRARIES "${ASSIMP_INTERFACE_LINK_LIBRARIES}")
    endif()
endif()
