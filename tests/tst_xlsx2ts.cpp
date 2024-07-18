#include "ConverterFactory.hpp"
#include "util.hpp"

#include <QApplication>

auto main() -> int
{
    bool ret = false;

    QApplication::setApplicationVersion("5.0.0");

    ret |= !test_conversion("scenario_after_version_4_5_0.xlsx",
                            "scenario_simple.ts",
                            ConverterFactory::ConversionType::Xlsx2Ts);

    ret |= !test_conversion("scenario_multilocation.xlsx",
                            "scenario_multilocation.ts",
                            ConverterFactory::ConversionType::Xlsx2Ts);

    return static_cast<int>(ret);
}
