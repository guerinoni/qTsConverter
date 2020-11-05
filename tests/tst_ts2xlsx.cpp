#include "ConverterFactory.hpp"

#include <QDebug>
#include <QFile>
#include <xlsx/xlsxdocument.h>

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

    QXlsx::Document xlsx(m_outputFile.c_str());

    int rowCount    = xlsx.dimension().rowCount();
    int columnCount = xlsx.dimension().columnCount();

    if (rowCount != 7 || columnCount != 6) {
        qDebug() << "The column size or the row size is wrong";
        return false;
    }

    if (xlsx.read(2, 2) != "Series" ||
        xlsx.read(2, 4) != "../themewidget.cpp - 289" ||
        xlsx.read(2, 5) != "../themewidget.cpp - 290" ||
        xlsx.read(2, 6) != "../themewidget.cpp - 291" ||
        xlsx.read(3, 6) != "../themewidget.cpp - 91" ||
        xlsx.read(7, 2) != "Anti-aliasing" ||
        xlsx.read(7, 4) != "../themewidget.ui - 49") {
        qWarning() << "Can't find one or more strings in the output file";
        return false;
    }

    return true;
}

int main()
{
    int ret  = !scenario1();
    int ret2 = !scenario_multiLocation();
    cleanup();
    return ret2;
    return ret && ret2;
}
