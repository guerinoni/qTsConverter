#pragma once

#include "Converter.hpp"
#include "TsParser.hpp"

#include <memory>

class CsvBuilder;

class Ts2CsvConverter : public Converter
{
  public:
    explicit Ts2CsvConverter(const std::string &input,
                             const std::string &output,
                             const std::string &field_sep,
                             const std::string &string_sep);

    void process() const override;

  private:
    TsParser parser_;
    std::shared_ptr<CsvBuilder> builder_;
};
