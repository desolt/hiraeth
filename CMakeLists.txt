cmake_minimum_required(VERSION 3.8)
project(hiraeth)

set(CMAKE_CXX_STANDARD 17)

# Dependencies:
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)

include_directories(include dep ${OPENGL_INCLUDE_DIR} ${BOOST_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES src/*.cpp include/*.hpp dep/*.c)
add_executable(hiraeth ${SOURCE_FILES})
target_link_libraries(hiraeth ${OPENGL_gl_LIBRARY} glfw ${BOOST_LIBRARIES})