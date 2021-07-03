cmake_minimum_required(VERSION 3.10)

project(
  qTsConverter
  LANGUAGES CXX
  VERSION "4.4.0"
  DESCRIPTION
    "Tool used to convert `.ts` file of Qt translation in other format more editable using an office suite."
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_INIT
    "-Werror"
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Warray-bounds"
    "-Wdouble-promotion"
    "-Weffc++"
    "-Wextra"
    "-Wimplicit-fallthrough"
    "-Winit-self"
    "-Wfloat-equal"
    "-Wformat=2"
    "-Wmissing-include-dirs"
    "-Wno-unused-const-variable"
    "-Wno-unused-function"
    "-Wnull-dereference"
    "-Wparentheses"
    "-Wpedantic"
    "-Wshift-overflow"
    "-Wshadow"
    "-Wstrict-aliasing=1"
    "-Wstrict-overflow=5"
    "-Wtautological-compare"
    "-Wuninitialized")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include(cmake/Sanitizers.cmake)
include(cmake/CompilerWarnings.cmake)

set(BUILD_TESTS
    OFF
    CACHE BOOL "build tests" FORCE)
set(STATIC_LIB
    ON
    CACHE BOOL "build as static lib if ON, otherwise build shared lib" FORCE)

add_subdirectory(3rd-party/qtcsv)
add_subdirectory(3rd-party/qtxlsx)
add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
add_subdirectory(data)
