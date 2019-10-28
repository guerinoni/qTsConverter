#pragma once

#include "Converter.hpp"
#include "TsBuilder.hpp"

#include <memory>

class CsvParser;

class Csv2TsConverter : public Converter
{
  public:
    explicit Csv2TsConverter(const std::string &input,
                             const std::string &output,
                             const std::string &field_sep,
                             const std::string &string_sep);

    void process() const override;

  private:
    std::shared_ptr<CsvParser> parser_;
    TsBuilder builder_;
};
