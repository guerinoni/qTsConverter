#include "ConverterFactory.hpp"

#include <QFile>
#include <QtDebug>

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
    expected.open(QIODevice::ReadOnly | QIODevice::Text);
    output.open(QIODevice::ReadOnly | QIODevice::Text);

    const auto o = output.readAll();
    const auto e = expected.readAll();

    expected.close();
    output.close();

    qDebug() << "e size: " << e.size() << ", e:\n" << e;
    qDebug() << "o size: " << o.size() << ", o:\n" << o;
    return o.size() == e.size() && o == e;
}
bool scenario2()
{
    const auto inputFile{ FILESPATH + std::string("/scenario2.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Csv, inputFile.c_str(),
        m_outputFile.c_str(), ";", "\"", "2.1");
    conv->process();
    QFile output(m_outputFile.c_str());
    if (!output.exists()) {
        return false;
    }

    QFile expected(FILESPATH + QString("/scenario2.csv"));
    expected.open(QIODevice::ReadOnly | QIODevice::Text);
    output.open(QIODevice::ReadOnly | QIODevice::Text);

    const auto o = output.readAll();
    const auto e = expected.readAll();

    expected.close();
    output.close();

    qDebug() << "e size: " << e.size() << ", e:\n" << e;
    qDebug() << "o size: " << o.size() << ", o:\n" << o;
    return o.size() == e.size() && o == e;
}

int main()
{
    int ret  = !scenario1();
    int ret2 = !scenario2();
    //    cleanup();
    return ret && ret2;
}
