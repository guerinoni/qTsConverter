#pragma once

#include <string>

struct CsvProperty {
    explicit CsvProperty(std::string field_sep, std::string string_sep) :
        field_separator{ field_sep }, string_separator{ string_sep }
    {
    }

    std::string field_separator;
    std::string string_separator;
};
