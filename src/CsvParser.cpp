#include "CsvParser.hpp"

#include <QDebug>
#include <QFile>
#include <include/qtcsv/reader.h>

CsvParser::CsvParser(InOutParameter parameter) : Parser{ std::move(parameter) }
{
}

std::pair<Translations, QString> CsvParser::parse() const
{
    auto list = QtCSV::Reader::readToList(
        m_ioParameter.inputFile.c_str(),
        m_ioParameter.csvProperty.field_separator.c_str(),
        m_ioParameter.csvProperty.string_separator.c_str());

    if (list.isEmpty()) {
        return std::make_pair(Translations(), "Source file empty!");
    }

    removeEmptyFrontBack(list);
    splitMergedString(list);
    splitByRow(list);

    Translations translations;
    TranslationContext context;
    TranslationMessage msg;

    list.pop_front();
    removeQuote(list);

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

    return std::make_pair(translations, "");
}

std::pair<QString, int> CsvParser::decodeLocation(QString str) const
{
    auto list = str.split(" - ");
    return std::make_pair(list.first(), list.last().toInt());
}

void CsvParser::removeEmptyFrontBack(QList<QStringList> &list) const
{
    for (int i = 0; i < list.size(); ++i) {
        decltype(auto) v = list[i];
        if (v.first().isEmpty()) {
            v.pop_front();
        }

        if (v.back().isEmpty()) {
            v.pop_back();
        }
    }
}

void CsvParser::splitMergedString(QList<QStringList> &list) const
{
    for (auto &l : list) {
        for (int i = 0; i < l.size(); ++i) {
            auto pair = l[i].split("\n");
            if (pair.size() == 1) {
                continue;
            }

            l.removeAt(i);
            l.insert(i, pair.first());
            l.insert(i + 1, pair.last());
        }
    }
}

void CsvParser::splitByRow(QList<QStringList> &list) const
{
    QList<QStringList> ret;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].size() == 8) {
            QStringList qsl;
            qsl << list[i][0] << list[i][1] << list[i][2] << list[i][3];
            ret.push_back(qsl);
            qsl.clear();

            qsl << list[i][4] << list[i][5] << list[i][6] << list[i][7];
            ret.push_back(qsl);
            continue;
        }
        ret.push_back(list[i]);
    }
    list = ret;
}

void CsvParser::removeQuote(QList<QStringList> &list) const
{
    for (auto &l : list) {
        for (auto &ll : l) {
            ll = ll.replace('"', "");
        }
    }
}
