#include "CsvParser.hpp"

#include <QDebug>
#include <QFile>
#include <include/qtcsv/reader.h>

CsvParser::CsvParser(CsvProperty property) : property_{ property } {}

Translations CsvParser::parse(const std::string &filename) const
{
    auto list = QtCSV::Reader::readToList(filename.c_str(),
                                          property_.field_separator.c_str(),
                                          property_.string_separator.c_str());
    if (list.isEmpty()) {
        qWarning() << "maybe is the file empty?";
        return {};
    }

    Translations translations;
    TranslationContext context;
    TranslationMessage msg;

    list.pop_front();
    for (const auto &l : list) {
        context.name    = l.at(0);
        msg.source      = l.at(1);
        msg.translation = l.at(2);
        msg.locations.emplace_back(decodeLocation(l.at(3)));
        context.messages.emplace_back(msg);

        auto it =
            std::find_if(translations.begin(), translations.end(),
                         [&](const auto &c) { return c.name == context.name; });
        if (it == translations.end()) {
            translations.emplace_back(context);
        } else {
            translations.at(std::distance(translations.begin(), it)) = context;
        }
        msg.locations.clear();
    }

    return translations;
}

std::pair<QString, int> CsvParser::decodeLocation(QString str) const
{
    auto list = str.split(" - ");
    return std::make_pair(list.first(), list.last().toInt());
}
