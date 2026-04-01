add_executable(ratplayer main.cpp)

target_link_libraries(ratplayer PRIVATE ratengine)

set_property(TARGET ratplayer PROPERTY CXX_STANDARD 20)
target_compile_definitions(ratplayer PRIVATE $<$<CONFIG:Release>:NDEBUG>)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(ratplayer PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(RAT_USE_IWYU)
  set_target_properties(ratplayer PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use;-Xiwyu;--error;-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp")
endif()
