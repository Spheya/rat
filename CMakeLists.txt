cmake_minimum_required(VERSION 3.22)
project("rat")

option(RAT_BUILD_EXAMPLES "Build example programs" ON)

include(FetchContent)

add_library(rat)
add_library(rat::rat ALIAS rat)

target_sources(rat PRIVATE "src/rat/platform/glfw/glfw_window.cpp" "src/rat/logger.cpp" "src/rat/rat.cpp" "src/rat/rendering/graphics_context.cpp" "src/rat/platform/opengl/opengl_graphics_context.cpp")

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
FetchContent_MakeAvailable(glfw glm)

add_subdirectory(external/glad)
target_link_libraries(rat
    PUBLIC glm
    PRIVATE glad glfw
)

if(MSVC)
  target_compile_options(rat PRIVATE /W4 /WX)
else()
  target_compile_options(rat PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(RAT_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()