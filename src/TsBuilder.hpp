#pragma once

#include "Builder.hpp"

class TsBuilder : public Builder
{
  public:
    explicit TsBuilder(InOutParameter parameter);

    void build(Translations &&trs) const override;
};
