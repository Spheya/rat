function(add_rat_extension name)
  add_library(${name} STATIC)
  target_link_libraries(ratengine PRIVATE ${name})
  target_link_libraries(${name} PRIVATE rat::core)
  if(RAT_BUILD_EDITOR)
    target_link_libraries(${name} PRIVATE rat::editor)
    target_compile_definitions(${name} PRIVATE RAT_EDITOR)
  endif()
endfunction()

function(init_rat_target name)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${name} PRIVATE
      -Weverything
      -Wno-c++98-c++11-c++14-c++17-compat-pedantic
      -Wno-c++98-compat-pedantic
      -Wno-c++11-compat-pedantic
      -Wno-c++14-compat-pedantic
      -Wno-c++17-compat-pedantic
      -Wno-c++20-compat-pedantic
      -Wno-c99-compat
      -Wno-unsafe-buffer-usage   # it's stupid
      -Wunused-macros            # seems to be incorrect sometimes?
      -fdiagnostics-show-template-tree
      -fdiagnostics-show-option
      -fdiagnostics-show-category=name
      -fvisibility=hidden
    )
  endif()
  if(RAT_USE_IWYU)
    set_target_properties(${name} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use;-Xiwyu;--error;-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp")
  endif()  
  target_compile_definitions(${name} PRIVATE $<$<CONFIG:Release>:NDEBUG>)
endfunction()
