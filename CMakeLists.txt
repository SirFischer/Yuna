cmake_minimum_required(VERSION 3.10)
project(Yuna VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Use Ninja as the preferred generator if available
find_program(NINJA_EXECUTABLE ninja)
if(NINJA_EXECUTABLE)
    set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "")
endif()

# Find required packages
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

# Add include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/includes/ai
    ${PROJECT_SOURCE_DIR}/includes/core
    ${PROJECT_SOURCE_DIR}/includes/math
    ${PROJECT_SOURCE_DIR}/includes/physics
    ${PROJECT_SOURCE_DIR}/includes/utils
    ${PROJECT_SOURCE_DIR}/includes/world
    ${PROJECT_SOURCE_DIR}/includes/ai/pathFinding
    ${PROJECT_SOURCE_DIR}/includes/core/console
    ${PROJECT_SOURCE_DIR}/includes/core/eventHandler
    ${PROJECT_SOURCE_DIR}/includes/core/resourceManager
    ${PROJECT_SOURCE_DIR}/includes/core/stateManager
    ${PROJECT_SOURCE_DIR}/includes/math/trigonometry
    ${PROJECT_SOURCE_DIR}/includes/physics/collisions
    ${PROJECT_SOURCE_DIR}/includes/utils/qTree
    ${PROJECT_SOURCE_DIR}/includes/world/objects
)

# Configure include paths for the source files
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${PROJECT_SOURCE_DIR}/includes")

# Recursive search for source files
file(GLOB_RECURSE YUNA_SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Configure mfGUI library
add_subdirectory(mfGUI)

# Create Yuna library
add_library(Yuna STATIC ${YUNA_SOURCES})
target_link_libraries(Yuna PUBLIC
    MFGUI
    sfml-graphics
    sfml-window
    sfml-system
)

# Add custom target for testing
add_custom_target(run_tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/Yuna
    DEPENDS Yuna
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running tests..."
)

# Configure sandbox if it exists
if(EXISTS "${PROJECT_SOURCE_DIR}/sandbox/CMakeLists.txt")
    add_subdirectory(sandbox)
endif()

# Installation rules
install(TARGETS Yuna
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY includes/
    DESTINATION include/Yuna
    FILES_MATCHING PATTERN "*.hpp"
)
