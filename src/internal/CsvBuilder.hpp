#pragma once

#include "Builder.hpp"

#include <include/qtcsv/stringdata.h>

class CsvBuilder : public Builder
{
  public:
    CsvBuilder() = delete;
    explicit CsvBuilder(InOutParameter &&parameter);
    CsvBuilder(const CsvBuilder &) = delete;
    CsvBuilder(CsvBuilder &&)      = delete;
    ~CsvBuilder() override         = default;

    CsvBuilder operator=(const CsvBuilder &) = delete;
    CsvBuilder operator=(CsvBuilder &&) = delete;

    bool build(const Result &res) const override;

  private:
    QtCSV::StringData addTsSupport() const;
};
