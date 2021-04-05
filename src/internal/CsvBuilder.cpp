#include "CsvBuilder.hpp"

#include "TitleHeaders.hpp"

#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <include/qtcsv/stringdata.h>
#include <include/qtcsv/writer.h>

CsvBuilder::CsvBuilder(InOutParameter &&parameter) : Builder{ parameter }
{
    if (!m_ioParameter.outputFile.endsWith("csv")) {
        m_ioParameter.outputFile += ".csv";
    }
}

auto CsvBuilder::build(const Translations &trs) const -> bool
{
    QStringList strList;
    strList << TitleHeader::Context << TitleHeader::Source
            << TitleHeader::Translation << TitleHeader::Location;

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

    if (!QtCSV::Writer::write(m_ioParameter.outputFile, strData,
                              m_ioParameter.csvProperty.field_separator,
                              m_ioParameter.csvProperty.string_separator)) {
        qWarning() << "error writing file";
        return false;
    }

    return true;
}
