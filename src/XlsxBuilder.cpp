#include "XlsxBuilder.hpp"

#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <xlsx/xlsxdocument.h>

void XlsxBuilder::build(const std::string &output_filename,
                        Translations trs) const
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

    if (!xlsx.saveAs(output_filename.c_str())) {
        qWarning() << "error writing file";
    }
}
