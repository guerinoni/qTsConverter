#include "ConverterFactory.hpp"

#include "CsvBuilder.hpp"
#include "CsvParser.hpp"
#include "TsBuilder.hpp"
#include "TsParser.hpp"
#include "XlsxBuilder.hpp"

#include <cassert>

std::unique_ptr<Converter>
ConverterFactory::make_converter(ConverterFactory::ConversionType type,
                                 const std::string &in, const std::string &out,
                                 const std::string &field_sep,
                                 const std::string &string_sep)
{
    switch (type) {
        case ConversionType::Ts2Csv:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(InOutParameter{
                    in, out, CsvProperty{ string_sep, field_sep } }),
                std::make_unique<CsvBuilder>(InOutParameter{
                    in, out, CsvProperty{ field_sep, string_sep } }));
            break;

        case ConversionType::Csv2Ts:
            return std::make_unique<Converter>(
                std::make_unique<CsvParser>(InOutParameter{
                    in, out, CsvProperty{ string_sep, field_sep } }),
                std::make_unique<TsBuilder>(InOutParameter{
                    in, out, CsvProperty{ field_sep, string_sep } }));
            break;

        case ConversionType::Ts2Xlsx:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(InOutParameter{
                    in, out, CsvProperty{ string_sep, field_sep } }),
                std::make_unique<XlsxBuilder>(InOutParameter{
                    in, out, CsvProperty{ field_sep, string_sep } }));
            break;

        default:
            break;
    }

    assert(false);
}
