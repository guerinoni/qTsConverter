#include "CsvBuilder.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>

CsvBuilder::CsvBuilder(CsvProperty property) : property_{ property } {}

void CsvBuilder::build(const std::string &output_filename,
                       Translations trs) const
{
    QFile file(output_filename.c_str());

    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "can't open file";
        return;
    }

    QTextStream output(&file);

    output << property_.string_separator.c_str() << "Input"
           << property_.string_separator.c_str()
           << property_.field_separator.c_str()
           << property_.string_separator.c_str() << "Output"
           << property_.string_separator.c_str() << "\n";

    for (const auto &tr : trs) {
        output << property_.string_separator.c_str() << tr.source
               << property_.string_separator.c_str()
               << property_.field_separator.c_str()
               << property_.string_separator.c_str() << tr.translation
               << property_.string_separator.c_str() << "\n";
    }

    file.close();
}
