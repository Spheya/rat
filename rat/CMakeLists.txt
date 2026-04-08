add_executable(rat main.cpp builder.cpp)
init_rat_target(rat)

if(WIN32)
  target_sources(rat PRIVATE rat.rc)
endif()

target_link_libraries(rat PRIVATE glfw)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(rat PRIVATE -Wno-cast-function-type-strict)
endif()