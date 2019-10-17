set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Quick Xml REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    Converter.hpp
    Converter.cpp
    Ts2CsvConverter.hpp
    Ts2CsvConverter.cpp
    ConverterGuiProxy.hpp
    ConverterGuiProxy.cpp
    ConverterFactory.hpp
    ConverterFactory.cpp
    TranslationObject.hpp
    TsParser.hpp
    TsParser.cpp
    CsvBuilder.hpp
    CsvBuilder.cpp
    CsvParser.hpp
    CsvParser.cpp
    Csv2TsConverter.hpp
    Csv2TsConverter.cpp
    TsBuilder.hpp
    TsBuilder.cpp
    qml.qrc)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Xml)
