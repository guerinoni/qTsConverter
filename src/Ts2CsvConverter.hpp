#pragma once

#include "Converter.hpp"
#include "CsvBuilder.hpp"
#include "TsParser.hpp"

class Ts2CsvConverter : public Converter
{
  public:
    explicit Ts2CsvConverter(const std::string &input,
                             const std::string &output);

    void process() const override;

  private:
    TsParser parser_;
    CsvBuilder builder_;
};
