#include "ConverterFactory.hpp"

#include "Csv2TsConverter.hpp"
#include "Ts2CsvConverter.hpp"

#include <cassert>

std::unique_ptr<Converter>
ConverterFactory::make_converter(ConverterFactory::ConversionType type,
                                 const std::string &in, const std::string &out)
{
    switch (type) {
        case ConversionType::Ts2Csv:
            return std::make_unique<Ts2CsvConverter>(in, out);
            break;

        case ConversionType::Csv2Ts:
            return std::make_unique<Csv2TsConverter>(in, out);
            break;

        default:
            break;
    }

    assert(false);
}
