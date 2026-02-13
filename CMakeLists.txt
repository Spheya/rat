cmake_minimum_required(VERSION 3.22)
project("rat")

option(RAT_BUILD_EXAMPLES "Build example programs" ON)

include(FetchContent)

add_library(rat)
add_library(rat::rat ALIAS rat)

file(GLOB_RECURSE CORE_HEADERS ./src/rat/core/*.hpp)
file(GLOB_RECURSE CORE_SOURCES ./src/rat/core/*.cpp)
file(GLOB_RECURSE RENDERING_HEADERS ./src/rat/rendering/*.hpp)
file(GLOB_RECURSE RENDERING_SOURCES ./src/rat/rendering/*.cpp)
file(GLOB_RECURSE PLATFORM_GLFW_HEADERS ./src/rat/platform/glfw/*.hpp)
file(GLOB_RECURSE PLATFORM_GLFW_SOURCES ./src/rat/platform/glfw/*.cpp)
file(GLOB_RECURSE PLATFORM_OPENGL_HEADERS ./src/rat/platform/opengl/*.hpp)
file(GLOB_RECURSE PLATFORM_OPENGL_SOURCES ./src/rat/platform/opengl/*.cpp)

source_group("Header Files/Core" FILES ${CORE_HEADERS})
source_group("Source Files/Core" FILES ${CORE_SOURCES})
source_group("Header Files/Rendering" FILES ${RENDERING_HEADERS})
source_group("Source Files/Rendering" FILES ${RENDERING_SOURCES})
source_group("Header Files/Platform/GLFW" FILES ${PLATFORM_GLFW_HEADERS})
source_group("Source Files/Platform/GLFW" FILES ${PLATFORM_GLFW_SOURCES})
source_group("Header Files/Platform/OpenGL" FILES ${PLATFORM_OPENGL_HEADERS})
source_group("Source Files/Platform/OpenGL" FILES ${PLATFORM_OPENGL_SOURCES})

target_sources(rat PRIVATE 
    ${CORE_HEADERS} ${CORE_SOURCES}
    ${RENDERING_HEADERS} ${RENDERING_SOURCES}
    ${PLATFORM_GLFW_HEADERS} ${PLATFORM_GLFW_SOURCES}
    ${PLATFORM_OPENGL_HEADERS} ${PLATFORM_OPENGL_SOURCES}
)

target_include_directories(rat PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:src>
)

set_target_properties(rat PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_CLANG_TIDY clang-tidy
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG 1.0.3
)

FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader
    GIT_TAG v2.0.0rc13
)

FetchContent_MakeAvailable(glfw glm tinyobjloader)

add_subdirectory(external/glad)
target_link_libraries(rat
    PUBLIC glm
    PRIVATE glad glfw tinyobjloader
)

if(MSVC)
  target_compile_options(rat PRIVATE /W4 /WX)
else()
  target_compile_options(rat PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(RAT_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()