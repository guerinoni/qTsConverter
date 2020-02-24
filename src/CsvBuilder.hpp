#pragma once

#include "Builder.hpp"

class CsvBuilder : public Builder
{
  public:
    explicit CsvBuilder(InOutParameter parameter);

    void build(Translations &&trs) const override;
};
