add_library(rateditor SHARED)
add_library(rat::editor ALIAS rateditor)
set_target_properties(rateditor PROPERTIES EXPORT_NAME editor)
init_rat_target(rateditor)

target_sources(rateditor
  PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES rat/editor/api.hpp rat/editor/editor.hpp
  PRIVATE
    rat/editor/editor.cpp
)
target_include_directories(rateditor PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)
target_compile_definitions(rateditor PUBLIC RAT_EDITOR PRIVATE RAT_EDITOR_EXPORT)

set_property(TARGET rateditor PROPERTY CXX_STANDARD 20)
