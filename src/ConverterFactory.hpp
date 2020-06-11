#pragma once

#include "Converter.hpp"

#include <memory>

class ConverterFactory
{
  public:
    enum ConversionType { Ts2Csv, Csv2Ts, Ts2Xlsx, Xlsx2Ts, Dummy };
    static std::unique_ptr<Converter>
    make_converter(ConversionType type, const std::string &in,
                   const std::string &out, const std::string &fieldSep,
                   const std::string &stringSep, const std::string &tsVersion);
};
