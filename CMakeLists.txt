cmake_minimum_required(VERSION 3.10)
project(MediaFramework VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include directories (allows #include "include/commands.h" and relative paths)
include_directories(${CMAKE_SOURCE_DIR})

# Automatically find all source files in app/ and src/ directories
file(GLOB_RECURSE APP_SOURCES "app/*.cpp")
file(GLOB_RECURSE SRC_SOURCES "src/*.cpp")
file(GLOB_RECURSE EXTERNAL_SOURCES "external/src/*.cpp")

# Create the executable "MediaApp"
add_executable(MediaApp
    main.cpp
    ${APP_SOURCES}
    ${SRC_SOURCES}
    ${EXTERNAL_SOURCES}
)

# Optional: Add compiler flags for warnings (good practice)
if(MSVC)
    target_compile_options(MediaApp PRIVATE /W4)
else()
    target_compile_options(MediaApp PRIVATE -Wall -Wextra)
endif()
