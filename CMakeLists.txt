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

FetchContent_Declare(
    VulkanHeaders
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG        v1.4.366
)
FetchContent_MakeAvailable(VulkanHeaders)

FetchContent_Declare(
    VulkanLoader
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Loader.git
    GIT_TAG        v1.4.363
)
FetchContent_MakeAvailable(VulkanLoader)

# Main executable
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})


# Include directories for your project and dependencies
target_include_directories(${PROJECT_NAME}
    PRIVATE include
    ${GLFW_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
    ${spdlog_SOURCE_DIR}/include
    ${vulkan_SOURCE_DIR}
)

# Link libraries to your executable
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        spdlog::spdlog_header_only
        Vulkan::Headers
        Vulkan::Loader
    PUBLIC
        glm::glm
)

# Custom Command: Re-run compile.sh when shaders or the script change
set(SHADER_STAMP ${CMAKE_CURRENT_BINARY_DIR}/shaders.stamp)

add_custom_command(
    OUTPUT ${SHADER_STAMP}
    DEPENDS 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/compile.sh
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/simple_shader.frag
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/simple_shader.vert
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/src/compile.sh
    COMMAND ${CMAKE_COMMAND} -E touch ${SHADER_STAMP}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    COMMENT "Shader inputs modified. Executing compile.sh..."
)

add_custom_target(CompileShaders DEPENDS ${SHADER_STAMP})

# Ensure compile.sh runs before building your main executable
add_dependencies(${PROJECT_NAME} CompileShaders)