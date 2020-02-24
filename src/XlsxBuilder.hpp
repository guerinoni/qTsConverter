#pragma once

#include "Builder.hpp"

class XlsxBuilder : public Builder
{
  public:
    explicit XlsxBuilder(InOutParameter parameter);

    void build(Translations &&trs) const override;
};
