#pragma once

#include <QString>

struct CsvProperty {
    CsvProperty() = default;
    explicit CsvProperty(const QString &field_sep, const QString &string_sep) :
        field_separator{ field_sep }, string_separator{ string_sep }
    {
    }
    CsvProperty(const CsvProperty &) = default;
    CsvProperty(CsvProperty &&)      = default;
    ~CsvProperty()                   = default;

    CsvProperty &operator=(const CsvProperty &) = default;
    CsvProperty &operator=(CsvProperty &&) = default;

    QString field_separator;
    QString string_separator;
};
