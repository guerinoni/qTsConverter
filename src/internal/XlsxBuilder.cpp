#include "XlsxBuilder.hpp"

#include "TitleHeaders.hpp"

#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <xlsx/xlsxdocument.h>

XlsxBuilder::XlsxBuilder(InOutParameter parameter) :
    Builder{ std::move(parameter) }
{
    if (!m_ioParameter.outputFile.endsWith("xlsx")) {
        m_ioParameter.outputFile += ".xlsx";
    }
}

auto XlsxBuilder::build(const Translations &trs) const -> bool
{
    QXlsx::Document xlsx;
    xlsx.write(1, 1, TitleHeader::Context);
    xlsx.write(1, 2, TitleHeader::Source);
    xlsx.write(1, 3, TitleHeader::Translation);
    xlsx.write(1, 4, TitleHeader::Location);

    int row{ 2 };
    int col{ 1 };
    for (const auto &tr : trs) {
        for (const auto &msg : tr.messages) {
            xlsx.write(row, col++, tr.name);
            xlsx.write(row, col++, msg.source);
            xlsx.write(row, col++, msg.translation);

            for (const auto &loc : msg.locations) {
                xlsx.write(
                    row, col++,
                    QString(loc.first + " - " + QString::number(loc.second)));
            }
            ++row;
            col = 1;
        }
    }

    if (!xlsx.saveAs(m_ioParameter.outputFile)) {
        qWarning() << "error writing file";
        return false;
    }

    return true;
}
