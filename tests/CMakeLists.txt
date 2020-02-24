set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
find_package(Qt5 COMPONENTS Core Gui Quick Xml Test REQUIRED)

add_executable(tests
    ../src/Converter.cpp            ../src/Converter.hpp
    ../src/Csv2TsConverter.cpp      ../src/Csv2TsConverter.hpp
    ../src/CsvBuilder.cpp           ../src/CsvBuilder.hpp
    ../src/CsvParser.cpp            ../src/CsvParser.hpp
    ../src/Ts2CsvConverter.cpp      ../src/Ts2CsvConverter.hpp
    ../src/TsBuilder.cpp            ../src/TsBuilder.hpp
    ../src/TsParser.cpp             ../src/TsParser.hpp

    tst_Ts2csv.cpp  tst_Ts2csv.hpp
    tst_Csv2ts.cpp  tst_Csv2ts.hpp
    main.cpp)

target_link_libraries(tests PRIVATE Qt5::Core Qt5::Xml Qt5::Test
                            PUBLIC qtcsv QtXlsxWriter)
add_definitions(-DFILESPATH=\"${CMAKE_CURRENT_SOURCE_DIR}/files\")
