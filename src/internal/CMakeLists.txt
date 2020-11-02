set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
find_package(
  Qt5
  COMPONENTS Core Gui Quick Widgets Xml
  REQUIRED)

add_library(
  internal
  Converter.cpp
  Converter.hpp
  ConverterFactory.cpp
  ConverterFactory.hpp
  ConverterGuiProxy.cpp
  ConverterGuiProxy.hpp
  CsvBuilder.cpp
  CsvBuilder.hpp
  CsvParser.cpp
  CsvParser.hpp
  TsBuilder.cpp
  TsBuilder.hpp
  TsParser.cpp
  TsParser.hpp
  XlsxBuilder.cpp
  XlsxBuilder.hpp
  XlsxParser.cpp
  XlsxParser.hpp
  Parser.cpp
  Parser.hpp
  Builder.cpp
  Builder.hpp
  ConversionModel.cpp
  ConversionModel.hpp
  TranslationObject.hpp
  CsvProperty.hpp
  InOutParameter.hpp
  TitleHeaders.hpp)

target_link_libraries(
  internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
