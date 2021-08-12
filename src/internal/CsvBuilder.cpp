#include "CsvBuilder.hpp"

#include "TitleHeaders.hpp"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QVersionNumber>
#include <QtDebug>
#include <include/qtcsv/writer.h>

CsvBuilder::CsvBuilder(InOutParameter &&parameter) : Builder{ parameter }
{
    if (!m_ioParameter.outputFile.endsWith("csv")) {
        m_ioParameter.outputFile += ".csv";
    }
}

auto CsvBuilder::build(const Result &res) const -> bool
{
    auto strData = addTsSupport();

    QStringList strList;
    strList << TitleHeader::Context << TitleHeader::Source
            << TitleHeader::Translation << TitleHeader::Location;

    strData.addRow(strList);

    for (const auto &tr : res.translantions) {
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

QtCSV::StringData CsvBuilder::addTsSupport() const
{
    QtCSV::StringData strData;
    const auto appVersion       = qApp->applicationVersion();
    const auto currentVersion   = QVersionNumber::fromString(appVersion);
    const auto TsSupportVersion = QVersionNumber(4, 5, 0);
    if (QVersionNumber::compare(currentVersion, TsSupportVersion) >= 0) {
        QStringList strList;
        strList << TitleHeader::TsVersion;
        strData.addRow(strList);
        strList.clear();
        strList << m_ioParameter.tsVersion;
        strData.addRow(strList);
        strList.clear();
    }

    return strData;
}
