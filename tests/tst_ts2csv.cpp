#include "ConverterFactory.hpp"
#include "util.hpp"

#include <QApplication>

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

    QApplication::setApplicationVersion("4.5.0");
    ret |= !test_conversion("scenario_multiline.ts",
                            "scenario_after_version_4_5_0.csv",
                            ConverterFactory::ConversionType::Ts2Csv);

    return static_cast<int>(ret);
}
