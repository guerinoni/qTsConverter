#include "CsvParser.hpp"

#include <QFile>
#include <include/qtcsv/reader.h>

CsvParser::CsvParser(InOutParameter parameter) : Parser{ std::move(parameter) }
{
}

auto CsvParser::parse() const -> Result
{
    auto list = QtCSV::Reader::readToList(
        m_ioParameter.inputFile, m_ioParameter.csvProperty.string_separator,
        m_ioParameter.csvProperty.field_separator);

    if (list.isEmpty()) {
        return Result{ "Source file empty!", Translations{},
                       InOutParameter{ m_ioParameter } };
    }

    removeEmptyFrontBack(list);
    splitByRow(list);

    Translations translations;
    TranslationContext context;
    TranslationMessage msg;

    list.pop_front();
    removeQuote(list);

    for (const QStringList &l : qAsConst(list)) {
        for (const auto &value : l) {
            context.name = l.at(kNameIndex);
        }

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

    return Result{ "", std::move(translations),
                   InOutParameter{ m_ioParameter } };
}

auto CsvParser::decodeLocation(const QString &str) -> std::pair<QString, int>
{
    auto list = str.split(QStringLiteral(" - "));
    return std::make_pair(list.first(), list.last().toInt());
}

void CsvParser::removeEmptyFrontBack(QList<QStringList> &list)
{
    for (auto &v : list) {
        if (v.first().isEmpty()) {
            v.pop_front();
        }

        if (v.back().isEmpty()) {
            v.pop_back();
        }
    }
}

void CsvParser::splitByRow(QList<QStringList> &list) const
{
    QList<QStringList> ret;
    for (auto &i : list) {
        QStringList qsl;
        int j = 0;
        if (i.size() >= kRowSize) {
            for (j = 0; j < i.size(); j++) {
                if (j >= m_minimumSize && !isLocation(i[j])) {
                    break;
                }

                qsl << i[j];
            }
            ret.push_back(qsl);
            qsl.clear();
        }

        for (int k = j; k < i.size(); k++) {
            qsl << i[k];
        }

        ret.push_back(qsl);
    }
    list = ret;
}

void CsvParser::removeQuote(QList<QStringList> &list)
{
    for (auto &l : list) {
        for (auto &ll : l) {
            ll = ll.replace('"', QString{});
        }
    }
}

auto CsvParser::isLocation(const QString &value) -> bool
{
    return value.contains("Location") ||
           value.contains(QRegExp(R"(\.\.\/.+-.[0-9]+)"));
}
