#include "ConverterFactory.hpp"

#include "Csv2TsConverter.hpp"
#include "Ts2CsvConverter.hpp"

#include <cassert>

std::unique_ptr<Converter>
ConverterFactory::make_converter(ConverterFactory::ConversionType type,
                                 const std::string &in, const std::string &out,
                                 const std::string &field_sep,
                                 const std::string &string_sep)
{
    switch (type) {
        case ConversionType::Ts2Csv:
            return std::make_unique<Ts2CsvConverter>(in, out, field_sep,
                                                     string_sep);
            break;

        case ConversionType::Csv2Ts:
            return std::make_unique<Csv2TsConverter>(in, out, field_sep,
                                                     string_sep);
            break;

        default:
            break;
    }

    assert(false);
}
