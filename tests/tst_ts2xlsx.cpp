#include "ConverterFactory.hpp"

#include <QFile>
#include <QtDebug>
#include <xlsx/xlsxdocument.h>

auto scenario_simple() -> bool
{
    auto output = FILESPATH + std::string("/output.xlsx");
    const auto inputFile{ FILESPATH + std::string("/scenario_simple.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Xlsx, inputFile.c_str(),
        output.c_str(), ";", "\"", "2.1");
    conv->process();

    QXlsx::Document xlsx(output.c_str());

    int rowCount    = xlsx.dimension().rowCount();
    int columnCount = xlsx.dimension().columnCount();

    if (rowCount != 5 || columnCount != 4) {
        qDebug() << "The column size or the row size is wrong";
        return false;
    }

    if (xlsx.read(2, 2) != "text" || xlsx.read(3, 2) != "map" ||
        xlsx.read(4, 2) != "cam" || xlsx.read(5, 2) != "checklist" ||
        xlsx.read(2, 4) != "../src/app/qml/MenuBar.qml - 17" ||
        xlsx.read(3, 4) != "../src/app/qml/MenuBar.qml - 28" ||
        xlsx.read(4, 4) != "../src/app/qml/MenuBar.qml - 43" ||
        xlsx.read(5, 4) != "../src/app/qml/MenuBar.qml - 58") {
        qWarning() << "Can't find one or more strings in the output file";
        return false;
    }

    return true;
}

auto scenario_multiLocation() -> bool
{
    auto output = FILESPATH + std::string("/output.xlsx");
    const auto inputFile{ FILESPATH +
                          std::string("/scenario_multilocation.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Xlsx, inputFile.c_str(),
        output.c_str(), ";", "\"", "2.1");
    conv->process();

    QXlsx::Document xlsx(output.c_str());

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

auto main() -> int
{
    bool ret = false;

    ret |= !scenario_simple();

    ret |= !scenario_multiLocation();

    return static_cast<int>(ret);
}
