cmake_minimum_required(VERSION 3.10)

project(qTsConverter LANGUAGES CXX VERSION "4.3.0")

include(cmake/StaticAnalyzers.cmake)

include(cmake/Sanitizers.cmake)

include(cmake/CompilerWarnings.cmake)

set(BUILD_TESTS OFF CACHE BOOL "build tests" FORCE)
set(STATIC_LIB ON CACHE BOOL "build as static lib if ON, otherwise build shared lib" FORCE)
add_subdirectory(3rd-party/qtcsv)
add_subdirectory(3rd-party/qtxlsx)
add_subdirectory(src)
add_subdirectory(tests)
