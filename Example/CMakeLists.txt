cmake_minimum_required(VERSION 3.30..)

set(Source Main.cpp)

add_executable(${PROJECT_NAME} ${Source})

target_link_libraries(${PROJECT_NAME} PUBLIC GFX::Core GFX::Graphics)

add_custom_command(
        TARGET OpenGL_Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:OpenGL_Game>/Assets)