include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
include_directories(${PROJECT_SOURCE_DIR}/src/internal)
find_package(
  Qt5
  COMPONENTS Core Gui Xml
  REQUIRED)

add_executable(tst_ts2csv tst_ts2csv.cpp)
add_executable(tst_csv2ts tst_csv2ts.cpp)
add_executable(tst_ts2xlsx tst_ts2xlsx.cpp)
add_executable(tst_xlsx2ts tst_xlsx2ts.cpp)

target_link_libraries(
  tst_ts2csv
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
target_link_libraries(
  tst_csv2ts
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
target_link_libraries(
  tst_ts2xlsx
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
target_link_libraries(
  tst_xlsx2ts
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)

add_definitions(-DFILESPATH=\"${CMAKE_CURRENT_SOURCE_DIR}/files\")

add_test("tst_ts2csv" tst_ts2csv)
add_test("tst_csv2ts" tst_csv2ts)
add_test("tst_xlsx2ts" tst_xlsx2ts)
add_test("tst_ts2xlsx" tst_ts2xlsx)
