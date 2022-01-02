add_definitions(
  -DVERSION=\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\"
)

add_subdirectory(internal)

include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtcsv)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)
include_directories(${PROJECT_SOURCE_DIR}/src/internal)

if(BUILD_CLI)
  add_definitions(-DONLY_CLI=1)
  find_package(
    Qt5
    COMPONENTS Core Xml
    REQUIRED)

  add_executable(${CMAKE_PROJECT_NAME} main.cpp)

  target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PUBLIC internal
    PRIVATE Qt5::Core Qt5::Xml
    PUBLIC qtcsv QtXlsxWriter)

endif()

if(NOT BUILD_CLI)
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
endif()

install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
