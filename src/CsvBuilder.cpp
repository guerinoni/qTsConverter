#include "CsvBuilder.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <include/qtcsv/stringdata.h>
#include <include/qtcsv/writer.h>

CsvBuilder::CsvBuilder(CsvProperty property) : property_{ property } {}

void CsvBuilder::build(const std::string &output_filename,
                       Translations trs) const
{
    QStringList strList;
    strList << "Input"
            << "Output";

    QtCSV::StringData strData;
    strData.addRow(strList);

    for (const auto &tr : trs) {
        strList.clear();
        strList << tr.source << tr.translation;
        strData.addRow(strList);
    }

    if (!QtCSV::Writer::write(output_filename.c_str(), strData,
                              property_.field_separator.c_str(),
                              property_.string_separator.c_str())) {
        qWarning() << "error writing file";
    }
}
