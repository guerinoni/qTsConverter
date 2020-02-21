add_subdirectory(Catch2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Quick Xml REQUIRED)

add_executable(tests
    ../src/Converter.cpp ../src/Converter.hpp
    ../src/Ts2CsvConverter.cpp ../src/Ts2CsvConverter.hpp
    ../src/TsParser.cpp ../src/TsParser.hpp
    ../src/CsvBuilder.cpp ../src/CsvBuilder.hpp
    ts2csv.cpp
    main.cpp)

target_link_libraries(tests Catch2::Catch2 Qt5::Core Qt5::Xml)
add_definitions(-DFILESPATH=\"${CMAKE_CURRENT_SOURCE_DIR}/files\")
