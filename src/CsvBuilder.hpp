#pragma once

#include "Builder.hpp"

class CsvBuilder : public Builder
{
  public:
    explicit CsvBuilder(InOutParameter parameter);

    bool build(const Translations &trs) const override;
};
