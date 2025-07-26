#include "CsvBuilder.hpp"

#include "TitleHeaders.hpp"

#include <QApplication>
#include <QFile>
#include <QFileInfo>
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
    auto strData = addTsSupport(res);

    QStringList strList;
    strList << TitleHeader::Context << TitleHeader::ID << TitleHeader::Source
            << TitleHeader::Translation << TitleHeader::TranslationType
            << TitleHeader::Comment << TitleHeader::ExtraComment
            << TitleHeader::TranslatorComment << TitleHeader::Location;
    strData.addRow(strList);

    for (const auto &tr : res.translantions) {
        for (const auto &msg : tr.messages) {
            strList.clear();
            strList << tr.name << msg.identifier << msg.source
                    << msg.translation << msg.translationtype << msg.comment
                    << msg.extracomment << msg.translatorcomment;
            for (const auto &loc : msg.locations) {
                strList << QString(loc.first + " - " + loc.second);
            }
            strData.addRow(strList);
        }
    }

    auto const info = QFileInfo(m_ioParameter.outputFile);
    if (!QtCSV::Writer::write(info.absoluteFilePath(), strData,
                              m_ioParameter.csvProperty.field_separator,
                              m_ioParameter.csvProperty.string_separator)) {
        qWarning() << "error writing file";
        return false;
    }

    return true;
}

QtCSV::StringData CsvBuilder::addTsSupport(const Result &res) const
{
    QtCSV::StringData strData;
    const auto appVersion       = qApp->applicationVersion();
    const auto currentVersion   = QVersionNumber::fromString(appVersion);
    const auto TsSupportVersion = QVersionNumber(4, 5, 0);
    if (QVersionNumber::compare(currentVersion, TsSupportVersion) >= 0) {
        QStringList strList;
        strList << TitleHeader::TsVersion << TitleHeader::SourceLanguage
                << TitleHeader::Language;
        strData.addRow(strList);
        strList.clear();
        strList << res.root.tsVersion << res.root.sourcelanguage
                << res.root.language;
        strData.addRow(strList);
        strList.clear();
    }

    return strData;
}
