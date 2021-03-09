#include "ConverterFactory.hpp"
#include "util.hpp"

auto main() -> int
{
    bool ret = false;

    ret |= !test_conversion("scenario_simple.ts", "scenario_simple.csv",
                            ConverterFactory::ConversionType::Ts2Csv);

    ret |= !test_conversion("scenario_multilocation.ts",
                            "scenario_multilocation.csv",
                            ConverterFactory::ConversionType::Ts2Csv);

    ret |= !test_conversion("scenario_multiline.ts", "scenario_multiline.csv",
                            ConverterFactory::ConversionType::Ts2Csv);

    return static_cast<int>(ret);
}
