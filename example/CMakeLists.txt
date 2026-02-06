add_executable(rat_example "main.cpp")
target_link_libraries(rat_example PRIVATE rat)

set_target_properties(rat_example PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_CLANG_TIDY clang-tidy
)

if(MSVC)
  target_compile_options(rat_example PRIVATE /W4 /WX)
else()
  target_compile_options(rat_example PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()