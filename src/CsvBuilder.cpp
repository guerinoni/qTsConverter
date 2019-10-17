#include "CsvBuilder.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>

void CsvBuilder::build(const std::string &output_filename,
                       Translations trs) const
{
    const auto sep = "~";
    QFile file(output_filename.c_str());

    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "can't open file";
        return;
    }

    QTextStream output(&file);

    output << "\""
           << "Input"
           << "\"" << sep << "\""
           << "Output"
           << "\"\n";

    auto id = 0;
    for (const auto &tr : trs) {
        output << "\"" << tr.source << "\"" << sep << "\"" << tr.translation
               << "\"\n";
    }

    file.close();
}
