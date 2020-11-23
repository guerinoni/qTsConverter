#include "CsvParser.hpp"

#include <QFile>
#include <include/qtcsv/reader.h>

CsvParser::CsvParser(InOutParameter parameter) : Parser{ std::move(parameter) }
{
}

std::pair<Translations, QString> CsvParser::parse() const
{
    auto list = QtCSV::Reader::readToList(
        m_ioParameter.inputFile, m_ioParameter.csvProperty.field_separator,
        m_ioParameter.csvProperty.string_separator);

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

    for (const QStringList &l : qAsConst(list)) {
        for (auto value : l)
            context.name = l.at(kNameIndex);
        msg.source      = l.at(kSourceIndex);
        msg.translation = l.at(kTranslationIndex);
        msg.locations.emplace_back(decodeLocation(l.at(kLocationsIndex)));

        for (int i = kLocationsIndex + 1; i < l.size(); i++) {
            msg.locations.emplace_back(decodeLocation(l.at(i)));
        }

        auto it =
            std::find_if(translations.begin(), translations.end(),
                         [&](const auto &c) { return c.name == context.name; });
        if (it == translations.end()) {
            context.messages.clear();
            context.messages.emplace_back(msg);
            translations.emplace_back(context);
        } else {
            context.messages.emplace_back(msg);
            translations.at(std::distance(translations.begin(), it)) = context;
        }
        msg.locations.clear();
    }

    return std::make_pair(translations, "");
}

std::pair<QString, int> CsvParser::decodeLocation(const QString &str) const
{
    auto list = str.split(QStringLiteral(" - "));
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
            auto pair = l[i].split(QStringLiteral("\n"));
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
        QStringList qsl;
        int j = 0;
        if (list[i].size() >= 8) {
            for (j = 0; j < list[i].size(); j++) {
                if (j >= m_minimumSize && !isLocation(list[i][j])) {
                    break;
                }
                qsl << list[i][j];
            }
            ret.push_back(qsl);
            qsl.clear();
        }
        for (int k = j; k < list[i].size(); k++) {
            qsl << list[i][k];
        }
        ret.push_back(qsl);
    }
    list = ret;
}

void CsvParser::removeQuote(QList<QStringList> &list) const
{
    for (auto &l : list) {
        for (auto &ll : l) {
            ll = ll.replace('"', QString{});
        }
    }
}

bool CsvParser::isLocation(QString value) const
{
    return value.contains("Location") ||
           value.contains(QRegExp("\\.\\.\\/.+-.[0-9]+"));
}
