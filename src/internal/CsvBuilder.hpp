#pragma once

#include "Builder.hpp"

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

    bool build(const Translations &trs) const override;
};
