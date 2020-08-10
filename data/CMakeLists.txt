install(FILES ${CMAKE_SOURCE_DIR}/README.md
    DESTINATION share/doc/qTsConverter)

install(FILES ${CMAKE_SOURCE_DIR}/LICENSE
    DESTINATION share/licenses/qTsConverter)

install(FILES ${CMAKE_SOURCE_DIR}/data/org.guerinoni.qTsConverter.desktop
    DESTINATION share/applications)

install(FILES ${CMAKE_SOURCE_DIR}/data/qTsConverter.desktop
    DESTINATION share/applications)

install(FILES ${CMAKE_SOURCE_DIR}/src/qml/assets/logos/vector/isolated-layout.svg
    DESTINATION share/pixmaps
    RENAME qTsConverter.svg)

install(FILES ${CMAKE_SOURCE_DIR}/src/qml/assets/logos/profile.png
    DESTINATION share/pixmaps
    RENAME qTsConverter.png)
