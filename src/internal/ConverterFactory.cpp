#include "ConverterFactory.hpp"

#include "CsvBuilder.hpp"
#include "CsvParser.hpp"
#include "TsBuilder.hpp"
#include "TsParser.hpp"
#include "XlsxBuilder.hpp"
#include "XlsxParser.hpp"

#include <cassert>

auto ConverterFactory::toString(ConverterFactory::ConversionType t) noexcept
    -> QString
{
    switch (t) {
        case Ts2Csv:
            return ".csv";

        case Ts2Xlsx:
            return ".xlsx";

        case Csv2Ts:
        case Xlsx2Ts:
            return ".ts";
    }

    return {};
}

auto ConverterFactory::fromString(const QString &suffixInput,
                                  const QString &suffixOutput) noexcept
    -> ConverterFactory::ConversionType
{
    if (suffixInput == QStringLiteral(".ts") &&
        suffixOutput == QStringLiteral(".csv")) {
        return Ts2Csv;
    }

    if (suffixInput == QStringLiteral(".ts") &&
        suffixOutput == QStringLiteral(".xlsx")) {
        return Ts2Xlsx;
    }

    if (suffixInput == QStringLiteral(".csv") &&
        suffixOutput == QStringLiteral(".ts")) {
        return Csv2Ts;
    }

    if (suffixInput == QStringLiteral(".xlsx") &&
        suffixOutput == QStringLiteral(".ts")) {
        return Xlsx2Ts;
    }

    return Dummy;
}

auto ConverterFactory::make_converter(ConverterFactory::ConversionType type,
                                      const QString &in, const QString &out,
                                      const QString &fieldSep,
                                      const QString &stringSep,
                                      const QString &tsVersion)
    -> std::unique_ptr<Converter>
{
    switch (type) {
        case ConversionType::Ts2Csv:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<CsvBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        case ConversionType::Csv2Ts:
            return std::make_unique<Converter>(
                std::make_unique<CsvParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<TsBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        case ConversionType::Ts2Xlsx:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<XlsxBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        case ConversionType::Xlsx2Ts:
            return std::make_unique<Converter>(
                std::make_unique<XlsxParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<TsBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        default:
            break;
    }

    assert(false);
    return {};
}
