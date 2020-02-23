set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
find_package(Qt5 COMPONENTS Core Gui Quick Xml REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    Converter.cpp           Converter.hpp
    ConverterFactory.cpp    ConverterFactory.hpp
    ConverterGuiProxy.cpp   ConverterGuiProxy.hpp
    Csv2TsConverter.cpp     Csv2TsConverter.hpp
    CsvBuilder.cpp          CsvBuilder.hpp
    CsvParser.cpp           CsvParser.hpp
    Ts2CsvConverter.cpp     Ts2CsvConverter.hpp
    TsBuilder.cpp           TsBuilder.hpp
    TsParser.cpp            TsParser.hpp
    main.cpp
    qml.qrc)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Xml
                                            PUBLIC qtcsv)
