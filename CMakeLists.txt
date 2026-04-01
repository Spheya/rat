cmake_minimum_required(VERSION 3.25)
project("rat")

option(RAT_BUILD_EXAMPLES "Build example programs" ON)
option(RAT_USE_IWYU "Use include-what-you-use" OFF)

include(FetchContent)

set(GLFW_INSTALL OFF CACHE BOOL OFF FORCE)
set(GLFW_DOCS OFF CACHE BOOL OFF FORCE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.4
  SYSTEM EXCLUDE_FROM_ALL)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 1.0.3
  SYSTEM EXCLUDE_FROM_ALL)

FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader
  GIT_TAG v2.0.0rc13
  SYSTEM EXCLUDE_FROM_ALL)

FetchContent_MakeAvailable(glfw glm tinyobjloader)
add_subdirectory(external/glad SYSTEM EXCLUDE_FROM_ALL)
add_subdirectory(external/mikktspace SYSTEM EXCLUDE_FROM_ALL)

add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(player)

# Todo: do a proper install instead of just building the executables
install(TARGETS rateditor ratplayer RUNTIME DESTINATION bin)
