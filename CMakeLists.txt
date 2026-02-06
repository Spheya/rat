cmake_minimum_required(VERSION 3.12)

project("rat")

option(RAT_BUILD_EXAMPLES "Build example programs" ON)

add_library(rat)
add_library(rat::rat ALIAS rat)

target_sources(rat PRIVATE src/rat.cpp)

target_include_directories(rat PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

set_target_properties(rat PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_CLANG_TIDY clang-tidy
)

if(MSVC)
  target_compile_options(rat PRIVATE /W4 /WX)
else()
  target_compile_options(rat PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(RAT_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()