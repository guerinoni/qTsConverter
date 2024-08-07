include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
include_directories(${PROJECT_SOURCE_DIR}/src/internal)
find_package(
  Qt5
  COMPONENTS Core Gui Quick Widgets Xml
  REQUIRED)

add_executable(tst_ts2csv tst_ts2csv.cpp)
add_executable(tst_csv2ts tst_csv2ts.cpp)
add_executable(tst_ts2xlsx tst_ts2xlsx.cpp)
add_executable(tst_xlsx2ts tst_xlsx2ts.cpp)

target_link_libraries(
  tst_ts2csv
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
target_link_libraries(
  tst_csv2ts
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
target_link_libraries(
  tst_ts2xlsx
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
target_link_libraries(
  tst_xlsx2ts
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)

add_definitions(-DFILESPATH=\"${CMAKE_CURRENT_SOURCE_DIR}/files\")

add_test("tst_ts2csv" tst_ts2csv)
add_test("tst_csv2ts" tst_csv2ts)
add_test("tst_ts2xlsx" tst_ts2xlsx)
add_test("tst_xlsx2ts" tst_xlsx2ts)

# copy required dlls to executables on windows
if(WIN32)
  cmake_minimum_required(VERSION 3.21)
  add_custom_command(
    TARGET tst_ts2csv
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tst_ts2csv>
            $<TARGET_FILE_DIR:tst_ts2csv>
    COMMAND_EXPAND_LISTS)
endif()
