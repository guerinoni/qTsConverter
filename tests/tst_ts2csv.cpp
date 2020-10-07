#include "../src/ConverterFactory.hpp"

#include <QFile>

const std::string m_outputFile{ FILESPATH + std::string("/output.csv") };

void cleanup()
{
    QFile::remove(m_outputFile.c_str());
}

bool scenario1()
{
    const auto inputFile{ FILESPATH + std::string("/scenario1.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Csv, inputFile.c_str(),
        m_outputFile.c_str(), ";", "\"", "2.1");
    conv->process();
    QFile output(m_outputFile.c_str());
    if (!output.exists()) {
        return false;
    }

    QFile expected(FILESPATH + QString("/scenario1.csv"));
    expected.open(QIODevice::ReadOnly);
    output.open(QIODevice::ReadOnly);

    const auto o = output.readAll();
    const auto e = expected.readAll();

    return o.size() == e.size() && o == e;
}

int main()
{
    int ret = !scenario1();
    cleanup();
    return ret;
}
