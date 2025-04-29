cmake_minimum_required(VERSION 3.10)
project(YunaSandbox VERSION 1.0.0 LANGUAGES CXX)

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
find_package(SFML 2 REQUIRED COMPONENTS graphics window system network audio)

# Add include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/states
    ${CMAKE_CURRENT_SOURCE_DIR}/../includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../mfGUI/include
)

# Recursive search for source files
file(GLOB_RECURSE SANDBOX_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Create Sandbox executable
add_executable(sandbox ${SANDBOX_SOURCES})

# Link with Yuna and SFML libraries
target_link_libraries(sandbox 
    ${CMAKE_BINARY_DIR}/../libYuna.a
    ${CMAKE_BINARY_DIR}/../mfGUI/lib/libMFGUId.a
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
    sfml-audio
)

# Add custom target for running the sandbox
add_custom_target(run_sandbox
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/sandbox
    DEPENDS sandbox
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running sandbox..."
)
