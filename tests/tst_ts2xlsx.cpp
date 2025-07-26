#include "ConverterFactory.hpp"

#include <QApplication>
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

    if (rowCount != 7 || columnCount != 9) {
        qDebug() << "The column size or the row size is wrong";
        QFile::remove(output.c_str());
        return false;
    }

    if (xlsx.read(4, 3) != "text" || xlsx.read(5, 3) != "map" ||
        xlsx.read(6, 3) != "cam" || xlsx.read(7, 3) != "checklist" ||
        xlsx.read(4, 9) != "../src/app/qml/MenuBar.qml - 17" ||
        xlsx.read(5, 9) != "../src/app/qml/MenuBar.qml - 28" ||
        xlsx.read(6, 9) != "../src/app/qml/MenuBar.qml - 43" ||
        xlsx.read(7, 9) != "../src/app/qml/MenuBar.qml - 58") {
        qWarning() << "Can't find one or more strings in the output file";
        QFile::remove(output.c_str());
        return false;
    }

    QFile::remove(output.c_str());
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

    if (rowCount != 9 || columnCount != 11) {
        qDebug() << "The column size or the row size is wrong";
        QFile::remove(output.c_str());
        return false;
    }

    if (xlsx.read(4, 3) != "Series" ||
        xlsx.read(4, 9) != "../themewidget.cpp - +289" ||
        xlsx.read(4, 10) != "../themewidget.cpp - 290" ||
        xlsx.read(4, 11) != "../themewidget.cpp - 291" ||
        xlsx.read(5, 11) != "../themewidget.cpp - -91" ||
        xlsx.read(9, 3) != "Anti-aliasing" ||
        xlsx.read(9, 9) != "../themewidget.ui - 49") {
        qWarning() << "Can't find one or more strings in the output file";
        QFile::remove(output.c_str());
        return false;
    }

    QFile::remove(output.c_str());
    return true;
}

auto scenario_ts_version() -> bool
{
    auto output = FILESPATH + std::string("/output.xlsx");
    const auto expected =
        FILESPATH + std::string("/scenario_after_version_4_5_0.xlsx");
    const auto inputFile{ FILESPATH + std::string("/scenario_simple.ts") };
    auto conv = ConverterFactory::make_converter(
        ConverterFactory::ConversionType::Ts2Xlsx, inputFile.c_str(),
        output.c_str(), ";", "\"", "2.1");
    conv->process();

    QXlsx::Document xlsxOutput(output.c_str());
    QXlsx::Document xlsxExpected(expected.c_str());

    if (xlsxOutput.dimension() != xlsxExpected.dimension()) {
        qDebug() << "dimension are different";
        QFile::remove(output.c_str());
        return false;
    }

    const auto rows = xlsxOutput.dimension().rowCount();
    const auto cols = xlsxOutput.dimension().columnCount();
    for (auto row = 1; row < rows; ++row) {
        for (auto col = 1; col < cols; ++col) {
            auto *const outCell = xlsxOutput.cellAt(row, col);
            auto *const expCell = xlsxExpected.cellAt(row, col);

            if (outCell == nullptr && expCell == nullptr) {
                continue;
            }

            if ((outCell == nullptr && expCell != nullptr) ||
                (outCell != nullptr && expCell == nullptr)) {
                qDebug() << "!different content in cell" << row << col;
                QFile::remove(output.c_str());
                return false;
            }

            const auto out = outCell->value();
            const auto exp = expCell->value();

            if (out.isNull() && exp.isNull()) {
                continue;
            }

            if (!out.isValid() && !exp.isValid()) {
                continue;
            }

            if (out.toString() != exp.toString()) {
                qDebug() << "different content" << out << exp;
                QFile::remove(output.c_str());
                return false;
            }
        }
    }

    QFile::remove(output.c_str());
    return true;
}

auto main() -> int
{
    bool ret = false;

    QApplication::setApplicationVersion("5.0.0");
    ret |= !scenario_simple();

    ret |= !scenario_multiLocation();

    ret |= !scenario_ts_version();

    return static_cast<int>(ret);
}
