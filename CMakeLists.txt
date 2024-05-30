cmake_minimum_required(VERSION 3.20)
project(Dynastinae VERSION 0.0.1)

# Set compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -g -fdiagnostics-color=always -Wextra -Wall -Wuninitialized -Winit-self -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Wcast-qual -Wswitch-default -Wconversion -Wunreachable-code")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) # Get headers

# Link files/home/vako/Documents/cpp/sdl2/Dynastinae/build/compile_commands.json
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*/*.cpp) # Get source files
add_executable(dynastinae ${SOURCE_FILES}) # Link sources files


# Libs
find_library(GL_LIB GL)
find_library(GLEW_LIB GLEW)
find_library(SDL2_LIB SDL2)
find_library(SDL2_IMAGE_LIB SDL2_image)
find_library(SDL2_MIXER_LIB SDL2_mixer)
find_library(SDL2_TTF_LIB SDL2_ttf)

if(GL_LIB)
	message(STATUS "Found GL library: ${GL_LIB}")
else()
	message(FATAL_ERROR "GL library not found")
endif()

if(GLEW_LIB)
	message(STATUS "Found GLEW library: ${GLEW_LIB}")
else()
	message(FATAL_ERROR "GLEW library not found")
endif()

if(SDL2_LIB)
	message(STATUS "Found SDL2 library: ${SDL2_LIB}")
else()
	message(FATAL_ERROR "SDL2 library not found")
endif()

if(SDL2_IMAGE_LIB)
	message(STATUS "Found SDL2 Image library: ${SDL2_IMAGE_LIB}")
else()
	message(FATAL_ERROR "SDL2 Image library not found")
endif()

if(SDL2_IMAGE_LIB)
	message(STATUS "Found SDL2 Mixer library: ${SDL2_MIXER_LIB}")
else()
	message(FATAL_ERROR "SDL2 Mixer library not found")
endif()

if(SDL2_TTF_LIB)
	message(STATUS "Found SDL2 TTF library: ${SDL2_TTF_LIB}")
else()
	message(FATAL_ERROR "SDL2 TTF library not found")
endif()

# Link libraries
target_link_libraries(dynastinae PRIVATE ${GL_LIB} ${GLEW_LIB} ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_MIXER_LIB} ${SDL2_TTF_LIB})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

