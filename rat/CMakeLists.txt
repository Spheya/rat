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
target_compile_definitions(rat PRIVATE UNICODE)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(rat PRIVATE -Wno-cast-function-type-strict)
endif()