#pragma once

#include "CsvProperty.hpp"

struct InOutParameter {
    InOutParameter()                       = default;
    InOutParameter(const InOutParameter &) = default;
    InOutParameter(InOutParameter &&)      = default;
    ~InOutParameter()                      = default;

    InOutParameter &operator=(const InOutParameter &) = default;
    InOutParameter &operator=(InOutParameter &&) = default;

    std::string inputFile;
    std::string outputFile;
    std::string tsVersion;
    CsvProperty csvProperty;
};
