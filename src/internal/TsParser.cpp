#include "TsParser.hpp"

#include <QFile>
#include <QtXml>

TsParser::TsParser(InOutParameter &&parameter) : Parser{ std::move(parameter) }
{
}

auto TsParser::parse() const -> Result
{
    QDomDocument doc;
    QFile file(m_ioParameter.inputFile);

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        return Result{ "Failed to open source!", {}, {}, {} };
    }

    RootAttr root;
    Translations translations;

    QDomElement docElem = doc.documentElement();
    root.tsVersion      = docElem.attributeNode("version").value();
    root.language       = docElem.attributeNode("language").value();
    root.sourcelanguage = docElem.attributeNode("sourcelanguage").value();

    auto contexts = doc.elementsByTagName(QStringLiteral("context"));
    for (int i = 0; i < contexts.size(); ++i) {
        auto nodeCtx = contexts.item(i);
        TranslationContext context;
        context.name = nodeCtx.firstChildElement(QStringLiteral("name")).text();
        auto msgs    = nodeCtx.childNodes();
        for (auto j = 0; j < msgs.size(); j++) {
            auto nodeMsg   = msgs.item(j);
            auto locations = nodeMsg.childNodes();
            if (nodeMsg.nodeName() != QStringLiteral("message")) {
                continue;
            }

            TranslationMessage msg;
            msg.identifier = nodeMsg.attributes().namedItem("id").nodeValue();
            //                nodeMsg.firstChildElement(QStringLiteral("message")).attributeNode("id").value();
            msg.source =
                nodeMsg.firstChildElement(QStringLiteral("source")).text();
            msg.translation =
                nodeMsg.firstChildElement(QStringLiteral("translation")).text();
            msg.translationtype =
                nodeMsg.firstChildElement(QStringLiteral("translation"))
                    .attributeNode("type")
                    .value();
            msg.comment =
                nodeMsg.firstChildElement(QStringLiteral("comment")).text();
            msg.extracomment =
                nodeMsg.firstChildElement(QStringLiteral("extracomment"))
                    .text();
            msg.translatorcomment =
                nodeMsg.firstChildElement(QStringLiteral("translatorcomment"))
                    .text();

            for (int k = 0; k < locations.size(); k++) {
                if (locations.at(k).nodeName() == "location") {
                    auto locMsg   = locations.item(k);
                    auto location = wrapLocation(locMsg);
                    msg.locations.emplace_back(location);
                }
            }
            context.messages.emplace_back(msg);
        }
        translations.emplace_back(context);
    }

    return Result{ "", std::move(translations), {}, std::move(root) };
}

auto TsParser::wrapLocation(const QDomNode &node) -> std::pair<QString, QString>
{
    auto location = node.toElement();
    auto fn       = location.attribute(QStringLiteral("filename"));
    auto line     = location.attribute(
        QStringLiteral("line")); // preserves "+20", "-3", etc.
    return std::make_pair(fn, line);
}
