#include "XlsxParser.hpp"

#include "TitleHeaders.hpp"

#include <QtDebug>
#include <xlsx/xlsxdocument.h>

XlsxParser::XlsxParser(InOutParameter &&parameter) :
    Parser{ std::move(parameter) }
{
}

std::pair<Translations, QString> XlsxParser::parse() const
{
    QXlsx::Document xlsx(m_ioParameter.inputFile);

    if (xlsx.read(1, 1) != TitleHeader::Context ||
        xlsx.read(1, 2) != TitleHeader::Source ||
        xlsx.read(1, 3) != TitleHeader::Translation ||
        xlsx.read(1, 4) != TitleHeader::Location) {
        qWarning() << "the xlsx file is not valid";
        return std::make_pair(Translations(),
                              "Invalid XLSX file, check the headers!");
    }

    Translations translations;
    TranslationContext context;
    TranslationMessage msg;

    const auto lastRow    = xlsx.dimension().lastRow();
    const auto lastColumn = xlsx.dimension().lastColumn();

    for (auto row = 2; row <= lastRow; ++row) {
        context.name    = xlsx.read(row, 1).toString();
        msg.source      = xlsx.read(row, 2).toString();
        msg.translation = xlsx.read(row, 3).toString();

        for (auto col = 4; col <= lastColumn; ++col) {
            const auto loc = xlsx.read(row, col).toString();
            auto list      = loc.split(QStringLiteral(" - "));
            msg.locations.emplace_back(
                std::make_pair(list.first(), list.last().toInt()));
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
