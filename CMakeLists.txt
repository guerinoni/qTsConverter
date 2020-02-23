cmake_minimum_required(VERSION 3.10)

project(qt-ts-csv LANGUAGES CXX VERSION "3.0.0")

add_subdirectory(3rd-party/qtcsv)
add_subdirectory(src)
add_subdirectory(tests)
