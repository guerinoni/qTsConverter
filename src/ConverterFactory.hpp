#pragma once

#include "Converter.hpp"

#include <memory>

class ConverterFactory
{
  public:
    enum ConversionType { Ts2Csv, Csv2Ts, Ts2Xlsx, Dummy };
    static std::unique_ptr<Converter>
    make_converter(ConversionType type, const std::string &in,
                   const std::string &out, const std::string &field_sep,
                   const std::string &string_sep);
};
