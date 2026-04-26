add_library(ratcore STATIC)
add_library(rat::core ALIAS ratcore)
set_target_properties(ratcore PROPERTIES EXPORT_NAME core)
init_rat_target(ratcore)

if(RAT_BUILD_EDITOR)
  target_compile_definitions(ratcore PRIVATE RAT_EDITOR)
endif()

target_link_libraries(ratcore PUBLIC glm PRIVATE glfw)

target_sources(ratcore
  PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
      rat/core/editorcontext.hpp
      rat/core/engine.hpp
      rat/core/logger.hpp
      rat/core/time.hpp
      rat/platform/opengl/opengl_graphics_context.hpp
      rat/rendering/interface/graphics_context.hpp
      rat/rendering/graphics.hpp
      rat/rendering/render_target.hpp
  PRIVATE
    rat/core/logger.cpp
    rat/core/engine.cpp
    rat/platform/opengl/opengl_graphics_context.cpp
)
target_include_directories(ratcore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(ratcore PRIVATE RAT_GLFW)
target_compile_definitions(ratcore PRIVATE RAT_OPENGL)
