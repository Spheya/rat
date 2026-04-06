cmake_minimum_required(VERSION 3.25)
project(rat)

include(CMakePackageConfigHelpers)
include(cmake/ratlib.cmake)

add_subdirectory(rat)
add_subdirectory(editor)

install(
  TARGETS rateditor rat
  EXPORT rat-targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  FILE_SET HEADERS DESTINATION include
)

install(
  EXPORT rat-targets
  FILE rat.cmake
  NAMESPACE rat::
  DESTINATION cmake
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/ratConfigVersion.cmake
  VERSION 1.0
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ratConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/ratConfig.cmake
  INSTALL_DESTINATION cmake
)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/ratConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/ratConfigVersion.cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ratlib.cmake
  DESTINATION cmake
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/engine/ DESTINATION src)
