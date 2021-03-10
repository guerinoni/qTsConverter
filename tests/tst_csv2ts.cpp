#include "ConverterFactory.hpp"
#include "util.hpp"

auto main() -> int
{
    bool ret = false;

    ret |= !test_conversion("scenario_simple.csv", "scenario_simple.ts",
                            ConverterFactory::ConversionType::Csv2Ts);

    ret |= !test_conversion("scenario_multilocation.csv",
                            "scenario_multilocation.ts",
                            ConverterFactory::ConversionType::Csv2Ts);

    ret |= !test_conversion("scenario_multiline.csv", "scenario_multiline.ts",
                            ConverterFactory::ConversionType::Csv2Ts);

    return static_cast<int>(ret);
}
