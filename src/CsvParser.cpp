#include "CsvParser.hpp"

#include <QDebug>
#include <QFile>

Translations CsvParser::parse(const std::string &filename) const
{
    const auto sep_line  = '\n';
    const auto sep_field = '~';

    QFile file(filename.c_str());

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "can't open file";
        return {};
    }

    std::vector<TranslationObj> tr_objs;

    auto content = file.readAll();
    auto list    = content.split(sep_line);
    for (const auto &l : list) {
        auto fields = l.split(sep_field);
        TranslationObj obj;
        obj.source      = fields.first();
        obj.translation = fields.last();
        tr_objs.emplace_back(obj);
    }

    tr_objs.erase(tr_objs.begin(), tr_objs.begin());
    return tr_objs;
}
