add_library(ratcore STATIC)
add_library(rat::core ALIAS ratcore)
set_target_properties(ratcore PROPERTIES EXPORT_NAME core)
init_rat_target(ratcore)

target_sources(ratcore
  PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES rat/logger.hpp
  PRIVATE
    rat/logger.cpp
)
target_include_directories(ratcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)
