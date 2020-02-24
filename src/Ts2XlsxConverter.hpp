#pragma once

#include "Converter.hpp"
#include "TsParser.hpp"

#include <memory>

class XlsxBuilder;

class Ts2XlsxConverter : public Converter
{
  public:
    explicit Ts2XlsxConverter(const std::string &input,
                              const std::string &output,
                              const std::string &field_sep,
                              const std::string &string_sep);

    void process() const override;

  private:
    TsParser m_parser;
    std::shared_ptr<XlsxBuilder> m_builder;
};
