#include "CsvParser.hpp"

#include <QDebug>
#include <QFile>

CsvParser::CsvParser(CsvProperty property) : property_{ property } {}

Translations CsvParser::parse(const std::string &filename) const
{
    const auto sep_line = '\n';
    QFile file(filename.c_str());

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "can't open file";
        return {};
    }

    std::vector<TranslationObj> tr_objs;

    auto content = file.readAll();
    auto list    = content.split(sep_line);
    for (const auto &l : list) {
        auto sep    = property_.field_separator.front();
        auto fields = l.split(sep);
        TranslationObj obj;
        obj.source =
            fields.first().replace(property_.string_separator.c_str(), "");
        obj.translation =
            fields.last().replace(property_.string_separator.c_str(), "");
        tr_objs.emplace_back(obj);
    }

    tr_objs.erase(tr_objs.begin(), tr_objs.begin());
    return tr_objs;
}
