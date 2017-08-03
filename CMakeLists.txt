cmake_minimum_required(VERSION 3.8)
project(hiraeth)

set(CMAKE_CXX_STANDARD 17)

# Dependencies:
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include ${OPENGL_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp src/game.cpp include/game.hpp include/engine/window.hpp src/engine/window.cpp)
add_executable(hiraeth ${SOURCE_FILES})
target_link_libraries(hiraeth ${OPENGL_gl_LIBRARY} glfw)