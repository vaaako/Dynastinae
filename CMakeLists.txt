cmake_minimum_required(VERSION 3.20)
project(Knuppel VERSION 0.0.1)

# Set compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -g -fdiagnostics-color=always -Wextra -Wall -Wuninitialized -Winit-self -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Wcast-qual -Wswitch-default -Wconversion -Wunreachable-code")

# Link files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*/*.cpp) # Get source files
add_executable(knuppel ${SOURCE_FILES}) # Link sources files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) # Get headers


# Libs
add_library(glad STATIC libs/glad/glad.c) # on libs folder
find_library(SDL2_LIBRARY SDL2) # Find local library
if(SDL2_LIBRARY)
    message(STATUS "Found SDL2 library: ${SDL2_LIBRARY}")
else()
    message(FATAL_ERROR "SDL2 library not found")
endif()

# Link libraries
target_link_libraries(knuppel PRIVATE glad ${SDL2_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

