cmake_minimum_required(VERSION 4.3)
project(cpp)

# Fetching dependencies using FetchContent
include(FetchContent)

# Set GLFW build options to disable tests, docs, and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Declare and make available GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# Declare and make available GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

# Declare and make available spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

# Declare and make available volk
FetchContent_Declare(
    volk
    GIT_REPOSITORY https://github.com/zeux/volk.git
)
FetchContent_MakeAvailable(volk)

# Main executable
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for your project and dependencies
target_include_directories(${PROJECT_NAME}
    PRIVATE include
    ${GLFW_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
    ${spdlog_SOURCE_DIR}/include
    ${volk_SOURCE_DIR}
)

# Link libraries to your executable
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        spdlog::spdlog_header_only
        volk
    PUBLIC
        glm::glm
)