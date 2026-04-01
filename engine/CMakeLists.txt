file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS ./src/rat/core/*.hpp)
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS ./src/rat/core/*.cpp)
file(GLOB_RECURSE RENDERING_HEADERS CONFIGURE_DEPENDS ./src/rat/rendering/*.hpp)
file(GLOB_RECURSE RENDERING_SOURCES CONFIGURE_DEPENDS ./src/rat/rendering/*.cpp)
file(GLOB_RECURSE PLATFORM_GLFW_HEADERS CONFIGURE_DEPENDS ./src/rat/platform/glfw/*.hpp)
file(GLOB_RECURSE PLATFORM_GLFW_SOURCES CONFIGURE_DEPENDS ./src/rat/platform/glfw/*.cpp)
file(GLOB_RECURSE PLATFORM_OPENGL_HEADERS CONFIGURE_DEPENDS ./src/rat/platform/opengl/*.hpp)
file(GLOB_RECURSE PLATFORM_OPENGL_SOURCES CONFIGURE_DEPENDS ./src/rat/platform/opengl/*.cpp)

source_group("Header Files/Core" FILES ${CORE_HEADERS})
source_group("Source Files/Core" FILES ${CORE_SOURCES})
source_group("Header Files/Rendering" FILES ${RENDERING_HEADERS})
source_group("Source Files/Rendering" FILES ${RENDERING_SOURCES})
source_group("Header Files/Platform/GLFW" FILES ${PLATFORM_GLFW_HEADERS})
source_group("Source Files/Platform/GLFW" FILES ${PLATFORM_GLFW_SOURCES})
source_group("Header Files/Platform/OpenGL" FILES ${PLATFORM_OPENGL_HEADERS})
source_group("Source Files/Platform/OpenGL" FILES ${PLATFORM_OPENGL_SOURCES})

add_library(ratengine
  ${CORE_HEADERS} ${CORE_SOURCES}
  ${RENDERING_HEADERS} ${RENDERING_SOURCES}
  ${PLATFORM_GLFW_HEADERS} ${PLATFORM_GLFW_SOURCES}
  ${PLATFORM_OPENGL_HEADERS} ${PLATFORM_OPENGL_SOURCES}
  ${LOADER_HEADERS} ${LOADER_SOURCES})

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
