#pragma once

#include <string>

struct CsvProperty {
    CsvProperty() = default;
    explicit CsvProperty(const std::string &field_sep,
                         const std::string &string_sep) :
        field_separator{ field_sep },
        string_separator{ string_sep }
    {
    }
    CsvProperty(const CsvProperty &) = default;
    CsvProperty(CsvProperty &&)      = default;
    ~CsvProperty()                   = default;

    CsvProperty &operator=(const CsvProperty &) = default;
    CsvProperty &operator=(CsvProperty &&) = default;

    std::string field_separator;
    std::string string_separator;
};
