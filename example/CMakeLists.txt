add_executable(rat_example "main.cpp")
target_link_libraries(rat_example PRIVATE rat)

set_target_properties(rat_example PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_CLANG_TIDY clang-tidy
)

add_custom_command(
    TARGET rat_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
)

if(MSVC)
  target_compile_options(rat_example PRIVATE /W4 /WX)
else()
  target_compile_options(rat_example PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()