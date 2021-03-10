#include "ConverterFactory.hpp"
#include "util.hpp"

auto main() -> int
{
    bool ret = false;

    ret |= !test_conversion("scenario_simple.xlsx", "scenario_simple.ts",
                            ConverterFactory::ConversionType::Xlsx2Ts);

    ret |= !test_conversion("scenario_multilocation.xlsx",
                            "scenario_multilocation.ts",
                            ConverterFactory::ConversionType::Xlsx2Ts);

    return static_cast<int>(ret);
}
