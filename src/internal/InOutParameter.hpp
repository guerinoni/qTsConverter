#pragma once

#include "CsvProperty.hpp"

#include <QString>

struct InOutParameter {
    InOutParameter()                       = default;
    InOutParameter(const InOutParameter &) = default;
    InOutParameter(InOutParameter &&)      = default;
    ~InOutParameter()                      = default;

    InOutParameter &operator=(const InOutParameter &) = default;
    InOutParameter &operator=(InOutParameter &&) = default;

    QString inputFile;
    QString outputFile;
    QString tsVersion;
    CsvProperty csvProperty;
    bool noVersion;
    bool noLocation;
};
