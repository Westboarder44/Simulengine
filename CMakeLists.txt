cmake_minimum_required(VERSION 3.20)
project(Simulengine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Header include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

include(FetchContent)

# GLFW (Disable testing/examples to keep build fast)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# 1. GLFW (Windowing)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.8)

# 2. GLM (Math)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 0.9.9.8)

# 3. spdlog (Logging)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.12.0)

# 4. Volk (Vulkan Meta-loader)
FetchContent_Declare(volk GIT_REPOSITORY https://github.com/zeux/volk.git)

FetchContent_MakeAvailable(glfw glm spdlog volk)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Include paths
target_include_directories(Simulengine PRIVATE include)

# Link libraries
target_link_libraries(Simulengine 
    PRIVATE 
        glfw 
        glm::glm 
        spdlog::spdlog_header_only 
        volk
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)