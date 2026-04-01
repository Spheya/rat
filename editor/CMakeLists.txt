add_executable(rateditor "src/main.cpp" "src/loader/mesh_loader.cpp")

target_link_libraries(rateditor PRIVATE ratengine mikktspace tinyobjloader)

set_property(TARGET rateditor PROPERTY OUTPUT_NAME "rat")
set_property(TARGET rateditor PROPERTY CXX_STANDARD 20)
target_compile_definitions(rateditor PRIVATE $<$<CONFIG:Release>:NDEBUG>)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(rateditor PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(RAT_USE_IWYU)
  set_target_properties(
    rateditor
    PROPERTIES
      CXX_INCLUDE_WHAT_YOU_USE
      "include-what-you-use;-Xiwyu;--error;-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp"
  )
endif()
