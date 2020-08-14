#pragma once

#include "Builder.hpp"

class XlsxBuilder : public Builder
{
  public:
    XlsxBuilder() = delete;
    explicit XlsxBuilder(InOutParameter parameter);
    XlsxBuilder(const XlsxBuilder &) = delete;
    XlsxBuilder(XlsxBuilder &&)      = delete;
    ~XlsxBuilder() override          = default;

    bool build(const Translations &trs) const override;
};
