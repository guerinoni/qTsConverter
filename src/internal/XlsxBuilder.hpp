#pragma once

#include "Builder.hpp"

#include <xlsx/xlsxdocument.h>

class XlsxBuilder : public Builder
{
  public:
    XlsxBuilder() = delete;
    explicit XlsxBuilder(InOutParameter parameter);
    XlsxBuilder(const XlsxBuilder &) = delete;
    XlsxBuilder(XlsxBuilder &&)      = delete;
    ~XlsxBuilder() override          = default;

    bool build(const Result &res) const override;

  private:
    void addTsSupport(int &row, int &col, QXlsx::Document &doc) const;
};
