add_library(ratcore STATIC)
add_library(rat::core ALIAS ratcore)
set_target_properties(ratcore PROPERTIES EXPORT_NAME core)
init_rat_target(ratcore)

if(RAT_BUILD_EDITOR)
  target_compile_definitions(ratcore PRIVATE RAT_EDITOR)
else()
  target_link_libraries(ratcore PRIVATE glfw)
endif()

target_link_libraries(ratcore PUBLIC glm)

target_sources(ratcore
  PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
      rat/rendering/render_target.hpp
      rat/engine.hpp
      rat/logger.hpp
  PRIVATE
    rat/logger.cpp
    rat/engine.cpp
)
target_include_directories(ratcore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
