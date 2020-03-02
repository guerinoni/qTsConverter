#pragma once

#include "Builder.hpp"

class XlsxBuilder : public Builder
{
  public:
    explicit XlsxBuilder(InOutParameter parameter);

    bool build(const Translations &trs) const override;
};
