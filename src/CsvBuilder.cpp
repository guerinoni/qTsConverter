#include "CsvBuilder.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <include/qtcsv/stringdata.h>
#include <include/qtcsv/writer.h>

CsvBuilder::CsvBuilder(InOutParameter parameter) : Builder{ parameter } {}

void CsvBuilder::build(Translations &&trs) const
{
    QStringList strList;
    strList << "Context"
            << "Source"
            << "Translation"
            << "Location";

    QtCSV::StringData strData;
    strData.addRow(strList);

    for (const auto &tr : trs) {
        for (const auto &msg : tr.messages) {
            strList.clear();
            strList << tr.name << msg.source << msg.translation;
            for (const auto &loc : msg.locations) {
                strList << QString(loc.first + " - " +
                                   QString::number(loc.second));
            }
            strData.addRow(strList);
        }
    }

    if (!QtCSV::Writer::write(
            m_ioParameter.outputDir.c_str(), strData,
            m_ioParameter.csvProperty.field_separator.c_str(),
            m_ioParameter.csvProperty.string_separator.c_str())) {
        qWarning() << "error writing file";
    }
}
