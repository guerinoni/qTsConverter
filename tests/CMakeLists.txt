add_subdirectory(Catch2)

add_executable(tests
    main.cpp
    ts2csv.cpp
    ../src/Converter.hpp
    ../src/Converter.cpp
    ../src/Ts2CsvConverter.hpp
    ../src/Ts2CsvConverter.cpp)

target_link_libraries(tests Catch2::Catch2)
