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
    return make_converter(type, in, out, fieldSep, stringSep, tsVersion, false,
                          false);
}
auto ConverterFactory::make_converter(ConverterFactory::ConversionType type,
                                      const QString &in, const QString &out,
                                      const QString &fieldSep,
                                      const QString &stringSep,
                                      const QString &tsVersion, bool noVersion,
                                      bool noLocation)
    -> std::unique_ptr<Converter>
{
    auto paramParser =
        InOutParameter{ in,        out,
                        tsVersion, CsvProperty{ stringSep, fieldSep },
                        noVersion, noLocation };
    auto paramBuilder =
        InOutParameter{ in,        out,
                        tsVersion, CsvProperty{ fieldSep, stringSep },
                        noVersion, noLocation };
    switch (type) {
        case ConversionType::Ts2Csv:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(std::move(paramParser)),
                std::make_unique<CsvBuilder>(std::move(paramBuilder)));
            break;

        case ConversionType::Csv2Ts:
            return std::make_unique<Converter>(
                std::make_unique<CsvParser>(std::move(paramParser)),
                std::make_unique<TsBuilder>(std::move(paramBuilder)));
            break;

        case ConversionType::Ts2Xlsx:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(std::move(paramParser)),
                std::make_unique<XlsxBuilder>(std::move(paramBuilder)));
            break;

        case ConversionType::Xlsx2Ts:
            return std::make_unique<Converter>(
                std::make_unique<XlsxParser>(std::move(paramParser)),
                std::make_unique<TsBuilder>(std::move(paramBuilder)));
            break;

        default:
            break;
    }

    assert(false);
    return {};
}
