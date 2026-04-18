cmake_minimum_required(VERSION 3.25)
project(myextension)

add_rat_extension(myextension)
target_compile_definitions(myextension PRIVATE MY_EXTENSION_EXPORT)
target_sources(myextension PRIVATE myextension.cpp)
