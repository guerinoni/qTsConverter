#include "CsvParser.hpp"

#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QVersionNumber>
#include <QtDebug>
#include <include/qtcsv/reader.h>

CsvParser::CsvParser(InOutParameter parameter) : Parser{ std::move(parameter) }
{
}

auto CsvParser::parse() const -> Result
{
    auto const info = QFileInfo(m_ioParameter.inputFile);
    auto list       = QtCSV::Reader::readToList(
        info.absoluteFilePath(), m_ioParameter.csvProperty.string_separator,
        m_ioParameter.csvProperty.field_separator);

    if (list.isEmpty()) {
        return Result{ "Source file empty!", {}, {}, {} };
    }
    removeEmptyFrontBack(list);
    // splitByRow(list);

    RootAttr root;

    const auto appVersion       = qApp->applicationVersion();
    const auto currentVersion   = QVersionNumber::fromString(appVersion);
    const auto TsSupportVersion = QVersionNumber(4, 5, 0);
    InOutParameter p{ "", "", m_ioParameter.tsVersion, {} };
    if (QVersionNumber::compare(currentVersion, TsSupportVersion) >= 0) {
        list.pop_front();
        root.tsVersion =
            list.first().isEmpty() ? QString{} : list.first().first();
        list.first().pop_front();
        root.sourcelanguage =
            list.first().isEmpty() ? QString{} : list.first().first();
        list.first().pop_front();
        root.language =
            list.first().isEmpty() ? QString{} : list.first().first();
        list.pop_front();
    }

    Translations translations;
    TranslationContext context;
    TranslationMessage msg;

    list.pop_front();
    removeQuote(list);

    for (const QStringList &l : qAsConst(list)) {
        //        for (const auto &value : l) {
        context.name = l.at(kNameIndex);
        //        }

        msg.identifier        = l.at(kIdIndex);
        msg.source            = l.at(kSourceIndex);
        msg.translation       = l.at(kTranslationIndex);
        msg.translationtype   = l.at(kTranslationTypeIndex);
        msg.comment           = l.at(kCommentIndex);
        msg.extracomment      = l.at(kExtraCommentIndex);
        msg.translatorcomment = l.at(kTranslatorCommentIndex);

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

    return Result{ "", std::move(translations), std::move(p), std::move(root) };
}

auto CsvParser::decodeLocation(const QString &str)
    -> std::pair<QString, QString>
{
    auto list = str.split(QStringLiteral(" - "));
    return std::make_pair(list.first(), list.last());
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
