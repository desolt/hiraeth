cmake_minimum_required(VERSION 3.1)
project(hiraeth)

# Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRCS src/*.cpp)

# Find all required libraries
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include ${SDL2_INCLUDE_DIRS})

add_executable(${CMAKE_PROJECT_NAME} ${SRCS} src/glad.c)
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})
