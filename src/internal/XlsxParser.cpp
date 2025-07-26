#include "XlsxParser.hpp"

#include "TitleHeaders.hpp"

#include <QApplication>
#include <QVersionNumber>
#include <xlsx/xlsxdocument.h>

XlsxParser::XlsxParser(InOutParameter &&parameter) :
    Parser{ std::move(parameter) }
{
}

auto XlsxParser::parse() const -> Result
{
    RootAttr root;
    Translations translations;
    TranslationContext context;
    TranslationMessage msg;

    QXlsx::Document xlsx(m_ioParameter.inputFile);

    auto offsetRow{ 0 };
    const auto appVersion       = qApp->applicationVersion();
    const auto currentVersion   = QVersionNumber::fromString(appVersion);
    const auto TsSupportVersion = QVersionNumber(4, 5, 0);
    InOutParameter p{ "", "", m_ioParameter.tsVersion, {} };
    if (QVersionNumber::compare(currentVersion, TsSupportVersion) >= 0) {
        root.tsVersion      = xlsx.read(2, 1).toString();
        root.sourcelanguage = xlsx.read(2, 2).toString();
        root.language       = xlsx.read(2, 3).toString();
        offsetRow           = 2;
    }

    if (xlsx.read(offsetRow + 1, 1) != TitleHeader::Context ||
        xlsx.read(offsetRow + 1, 2) != TitleHeader::ID ||
        xlsx.read(offsetRow + 1, 3) != TitleHeader::Source ||
        xlsx.read(offsetRow + 1, 4) != TitleHeader::Translation ||
        xlsx.read(offsetRow + 1, 5) != TitleHeader::TranslationType ||
        xlsx.read(offsetRow + 1, 6) != TitleHeader::Comment ||
        xlsx.read(offsetRow + 1, 7) != TitleHeader::ExtraComment ||
        xlsx.read(offsetRow + 1, 8) != TitleHeader::TranslatorComment ||
        xlsx.read(offsetRow + 1, 9) != TitleHeader::Location) {
        return Result{ "Invalid XLSX file, check the headers!", {}, {}, {} };
    }

    const auto lastRow    = xlsx.dimension().lastRow();
    const auto lastColumn = xlsx.dimension().lastColumn();

    for (auto row = 4; row <= lastRow; ++row) {
        context.name          = xlsx.read(row, 1).toString();
        msg.identifier        = xlsx.read(row, 2).toString();
        msg.source            = xlsx.read(row, 3).toString();
        msg.translation       = xlsx.read(row, 4).toString();
        msg.translationtype   = xlsx.read(row, 5).toString();
        msg.comment           = xlsx.read(row, 6).toString();
        msg.extracomment      = xlsx.read(row, 7).toString();
        msg.translatorcomment = xlsx.read(row, 8).toString();

        for (auto col = 9; col <= lastColumn; ++col) {
            const auto loc = xlsx.read(row, col).toString();
            if (loc.isEmpty()) {
                break;
            }
            auto list = loc.split(QStringLiteral(" - "));
            msg.locations.emplace_back(
                std::make_pair(list.first(), list.last()));
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
