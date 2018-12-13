cmake_minimum_required(VERSION 3.12)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(sidekick_flags)

add_executable(bla main.cpp)
sidekick_apply_flags(bla)
