#include "../src/ConverterFactory.hpp"

#include <QFile>

const std::string m_outputFile{ FILESPATH + std::string("/output.ts") };

void cleanup()
{
    QFile::remove(m_outputFile.c_str());
}

bool scenario1()
{
    const auto inputFile{ FILESPATH + std::string("/scenario1.csv") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Csv2Ts, inputFile.c_str(),
        m_outputFile.c_str(), ";", "\"", "2.1");
    conv->process();
    QFile output(m_outputFile.c_str());
    if (!output.exists()) {
        return false;
    }

    QFile expected(FILESPATH + QString("/scenario1.ts"));
    expected.open(QIODevice::ReadOnly | QIODevice::Text);
    output.open(QIODevice::ReadOnly | QIODevice::Text);

    const auto o = output.readAll();
    const auto e = expected.readAll();

    expected.close();
    output.close();

    return o.size() == e.size() && o == e;
}

int main()
{
    int ret = !scenario1();
    cleanup();
    return ret;
}
