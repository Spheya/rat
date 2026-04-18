add_executable(rat main.cpp builder.cpp)
init_rat_target(rat)

if(WIN32)
  target_sources(rat PRIVATE rat.rc)
endif()

target_link_libraries(rat PRIVATE glfw)

add_custom_command(TARGET rat POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:glfw>
    $<TARGET_FILE_DIR:rat>
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(rat PRIVATE -Wno-cast-function-type-strict)
endif()

target_include_directories(rat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/core/)