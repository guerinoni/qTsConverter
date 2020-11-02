#include "../src/ConverterFactory.hpp"

#include <QDebug>
#include <QFile>

const std::string m_outputFile{ FILESPATH + std::string("/output.xlsx") };

void cleanup()
{
    QFile::remove(m_outputFile.c_str());
}

bool scenario1()
{
    const auto inputFile{ FILESPATH + std::string("/scenario1.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Xlsx, inputFile.c_str(),
        m_outputFile.c_str(), ";", "\"", "2.1");
    conv->process();
    QFile output(m_outputFile.c_str());
    if (!output.exists()) {
        return false;
    }

    QFile expected(FILESPATH + QString("/scenario1.xlsx"));
    expected.open(QIODevice::ReadOnly | QIODevice::Text);
    output.open(QIODevice::ReadOnly | QIODevice::Text);

    const auto o = output.readAll();
    const auto e = expected.readAll();

    expected.close();
    output.close();

    qDebug() << "o: " << o << "e: " << e;

    return o.size() == e.size() && o == e;
}
bool scenario_multiLocation()
{
    const auto inputFile{ FILESPATH +
                          std::string("/scenario_multiLocation.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Xlsx, inputFile.c_str(),
        m_outputFile.c_str(), ";", "\"", "2.1");
    conv->process();

    QFile output(m_outputFile.c_str());
    if (!output.exists()) {
        return false;
    }

    QFile expected(FILESPATH + QString("/scenario_multiLocation.xlsx"));
    expected.open(QIODevice::ReadOnly | QIODevice::Text);
    output.open(QIODevice::ReadOnly | QIODevice::Text);

    const auto o = output.readAll();
    const auto e = expected.readAll();

    expected.close();
    output.close();

    qDebug() << "o: " << o << "\n*******************\ne: " << e;

    return o.size() == e.size() && o == e;
}

int main()
{
    //    int ret = !scenario1();
    //    int ret = !scenario1();
    int ret2 = !scenario_multiLocation();
    //    cleanup();
    return ret2;
    //    return ret && ret2;
}
