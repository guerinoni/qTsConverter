include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
find_package(
  Qt5
  COMPONENTS Core Gui Quick Widgets Xml
  REQUIRED)

set(SW_VERSION ${PROJECT_VERSION})
set(SW_DESCRIPTION ${PROJECT_DESCRIPTION})
configure_file(${PROJECT_SOURCE_DIR}/src/internal/version.h.in
               ${PROJECT_SOURCE_DIR}/src/internal/version.hpp)

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
  TitleHeaders.hpp
  CliRunner.hpp
  CliRunner.cpp
  Result.hpp)

target_link_libraries(
  internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)
