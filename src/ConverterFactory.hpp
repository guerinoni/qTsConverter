#pragma once

#include "Converter.hpp"

#include <memory>

class ConverterFactory
{
  public:
    enum ConversionType { Ts2Csv, Csv2Ts, Ts2Xlsx, Xlsx2Ts, Dummy };
    static std::unique_ptr<Converter>
    make_converter(ConversionType type, const QString &in, const QString &out,
                   const QString &fieldSep, const QString &stringSep,
                   const QString &tsVersion);
};
