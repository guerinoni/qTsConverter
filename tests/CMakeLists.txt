file(GLOB_RECURSE TESTS CONFIGURE_DEPENDS "*.cpp")

foreach(TEST_FILE ${TESTS})
    file(RELATIVE_PATH TEST_FILE_REL ${CMAKE_SOURCE_DIR}/tests ${TEST_FILE})
    string(REPLACE ".cpp" "" TEST_NAME ${TEST_FILE_REL})

    include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
    include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
    find_package(Qt5 COMPONENTS Core Gui Xml REQUIRED)

    add_executable(${TEST_NAME}
         ../src/Converter.cpp           ../src/Converter.hpp
         ../src/ConverterFactory.cpp    ../src/ConverterFactory.hpp
         ../src/CsvBuilder.cpp          ../src/CsvBuilder.hpp
         ../src/CsvParser.cpp           ../src/CsvParser.hpp
         ../src/TsBuilder.cpp           ../src/TsBuilder.hpp
         ../src/TsParser.cpp            ../src/TsParser.hpp
         ../src/XlsxBuilder.cpp         ../src/XlsxBuilder.hpp
         ../src/XlsxParser.cpp          ../src/XlsxParser.hpp
         ../src/Parser.cpp              ../src/Parser.hpp
         ../src/Builder.cpp             ../src/Builder.hpp
         ../src/TranslationObject.hpp
         ../src/CsvProperty.hpp
         ../src/InOutParameter.hpp
         ../src/TitleHeaders.hpp
         ${TEST_FILE}
     )

    target_link_libraries(${TEST_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Xml
                                       PUBLIC qtcsv QtXlsxWriter)

    add_definitions(-DFILESPATH=\"${CMAKE_CURRENT_SOURCE_DIR}/files\")

    add_test("${TEST_NAME}" ${TEST_NAME})
endforeach()
