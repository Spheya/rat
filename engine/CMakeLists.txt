add_library(ratengine "src/rat/core/logger.cpp" "src/rat/core/rat.cpp" "src/rat/platform/glfw/glfw_window.cpp")

target_include_directories(ratengine PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)

target_link_libraries(
  ratengine
  PUBLIC glm
  PRIVATE glad glfw)

set_property(TARGET ratengine PROPERTY CXX_STANDARD 20)
target_compile_definitions(ratengine PRIVATE $<$<CONFIG:Release>:NDEBUG>)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(ratengine PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(RAT_USE_IWYU)
  set_target_properties(ratengine PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use;-Xiwyu;--error;-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp")
endif()
