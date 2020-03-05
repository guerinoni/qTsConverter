cmake_minimum_required(VERSION 3.10)

project(qt-ts-csv LANGUAGES CXX VERSION "3.2.0")

set(BUILD_TESTS OFF CACHE BOOL "build tests" FORCE)
set(STATIC_LIB ON CACHE BOOL "build as static lib if ON, otherwise build shared lib" FORCE)
add_subdirectory(3rd-party/qtcsv)
add_subdirectory(3rd-party/qtxlsx)
add_subdirectory(src)
add_subdirectory(tests)
