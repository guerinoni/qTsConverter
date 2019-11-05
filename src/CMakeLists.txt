set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Quick Xml REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    Converter.cpp
    ConverterFactory.cpp
    ConverterGuiProxy.cpp
    Csv2TsConverter.cpp
    CsvBuilder.cpp
    CsvParser.cpp
    Ts2CsvConverter.cpp
    TsBuilder.cpp
    TsParser.cpp
    main.cpp
    qml.qrc)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Xml)
