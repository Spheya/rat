cmake_minimum_required(VERSION 3.25)
project(sandbox)

# Make sure to build the engine from our source directory
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/ratlib.cmake)
add_subdirectory(../../ rat)

message("generating .rat folder")
execute_process(COMMAND rat generate ${CMAKE_CURRENT_SOURCE_DIR}/sandbox.ratproject)
message("finished generating .rat folder")
add_subdirectory(.rat)
