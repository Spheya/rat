add_executable(rat main.cpp builder.cpp)
init_rat_target(rat)

if(WIN32)
  target_sources(rat PRIVATE rat.rc)
endif()

target_link_libraries(rat PRIVATE rateditor)

add_custom_command(
  TARGET rat
  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:rateditor> $<TARGET_FILE_DIR:rat>
    VERBATIM
)

set_property(TARGET rat PROPERTY CXX_STANDARD 20)
target_compile_definitions(rat PRIVATE $<$<CONFIG:Release>:NDEBUG> UNICODE)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(rat PRIVATE -Wno-cast-function-type-strict)
endif()
if(RAT_USE_IWYU)
  set_target_properties(rat PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use;-Xiwyu;--error;-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp")
endif()