cmake_minimum_required(VERSION 3.12)

project(sidekick)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(sidekick_flags)

enable_testing()

add_subdirectory(sources)

