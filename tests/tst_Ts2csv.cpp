#include "tst_Ts2csv.hpp"

#include "../src/ConverterFactory.hpp"

void tst_Ts2Csv::cleanup()
{
    QFile::remove(m_outputFile.c_str());
}

void tst_Ts2Csv::checkScenario1()
{
    const auto inputFile{ FILESPATH + std::string("/scenario1.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Csv, inputFile.c_str(),
        m_outputFile.c_str(), ";", "\"", "2.1");
    conv->process();
    QFile out(m_outputFile.c_str());
    QVERIFY(out.exists());

    QFile expected(FILESPATH + QString("/scenario1.csv"));
    expected.open(QIODevice::ReadOnly);
    out.open(QIODevice::ReadOnly);

    const auto o = out.readAll();
    const auto e = expected.readAll();

    QCOMPARE(o.size(), e.size());
    QCOMPARE(o, e);
}
