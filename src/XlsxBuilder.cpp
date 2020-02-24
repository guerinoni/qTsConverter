#include "XlsxBuilder.hpp"

#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <xlsx/xlsxdocument.h>

XlsxBuilder::XlsxBuilder(InOutParameter parameter) :
    Builder{ std::move(parameter) }
{
}

void XlsxBuilder::build(Translations &&trs) const
{
    QXlsx::Document xlsx;
    xlsx.write(1, 1, "Context");
    xlsx.write(1, 2, "Source");
    xlsx.write(1, 3, "Translation");
    xlsx.write(1, 4, "Location");

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

    if (!xlsx.saveAs(m_ioParameter.outputDir.c_str() +
                     QString("/output.xlsx"))) {
        qWarning() << "error writing file";
    }
}
