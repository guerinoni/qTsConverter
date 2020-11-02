set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(internal)

include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
include_directories(${PROJECT_SOURCE_DIR}/src/internal)
find_package(
  Qt5
  COMPONENTS Core Gui Quick Widgets Xml
  REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp qml/qml.qrc)

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PUBLIC internal
  PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Xml
  PUBLIC qtcsv QtXlsxWriter)

add_definitions(
  -DVERSION=\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\"
)

install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
