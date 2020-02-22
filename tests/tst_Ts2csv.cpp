#include "tst_Ts2csv.hpp"

#include "../src/Ts2CsvConverter.hpp"

void tst_Ts2Csv::cleanup()
{
    QFile::remove(m_outputFile.c_str());
}

void tst_Ts2Csv::checkScenario1()
{
    const auto inputFile{ FILESPATH + std::string("/scenario1.ts") };
    Ts2CsvConverter ts2csv(inputFile, FILESPATH, ";", "\"");
    ts2csv.process();
    QFile out(m_outputFile.c_str());
    QVERIFY(out.exists());

    QFile expected(FILESPATH + QString("/scenario1.csv"));
    expected.open(QIODevice::ReadOnly);
    out.open(QIODevice::ReadOnly);

    QCOMPARE(expected.readAll(), out.readAll());
}
