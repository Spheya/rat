add_library(mikktspace STATIC "src/mikktspace.c")
target_include_directories(mikktspace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)