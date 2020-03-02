#pragma once

#include "Builder.hpp"

class TsBuilder : public Builder
{
  public:
    explicit TsBuilder(InOutParameter parameter);

    bool build(const Translations &trs) const override;
};
