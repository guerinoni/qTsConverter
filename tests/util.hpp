#include <ConverterFactory.hpp>
#include <QFile>

auto test_conversion(std::string &&input, std::string &&expect,
                     ConverterFactory::ConversionType typeOfConvesion) -> bool
{
    auto output = FILESPATH + std::string("/output");
    switch (typeOfConvesion) {
        case ConverterFactory::ConversionType::Csv2Ts:
        case ConverterFactory::ConversionType::Xlsx2Ts:
            output += ".ts";
            break;

        case ConverterFactory::ConversionType::Ts2Csv:
            output += ".csv";
            break;

        case ConverterFactory::ConversionType::Ts2Xlsx:
            output += ".xlsx";
            break;

        default:
            break;
    }

    const auto in = FILESPATH + std::string("/") + input;
    auto conv     = ConverterFactory::make_converter(
        typeOfConvesion, in.c_str(), output.c_str(), ";", "\"", "2.1");

    conv->process();

    QFile out(output.c_str());
    if (!out.exists()) {
        return false;
    }

    QFile expected(FILESPATH + QStringLiteral("/") +
                   QString::fromStdString(expect));
    expected.open(QIODevice::ReadOnly | QIODevice::Text);
    out.open(QIODevice::ReadOnly | QIODevice::Text);

    const auto o = out.readAll();
    const auto e = expected.readAll();

    expected.close();
    out.close();
    out.remove();

    return o.size() == e.size() && o == e;
}
