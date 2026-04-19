if(NOT TARGET glfw)
  set(GLFW_BUILD_DOCS OFF CACHE STRING "" FORCE)
  add_subdirectory(external/glfw EXCLUDE_FROM_ALL SYSTEM)
endif()

add_subdirectory(external/glm EXCLUDE_FROM_ALL SYSTEM)
add_subdirectory(external/glad EXCLUDE_FROM_ALL SYSTEM)
add_subdirectory(core)