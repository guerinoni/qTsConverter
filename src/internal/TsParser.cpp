#include "TsParser.hpp"

#include <QFile>
#include <QtXml>

TsParser::TsParser(InOutParameter &&parameter) : Parser{ std::move(parameter) }
{
}

std::pair<Translations, QString> TsParser::parse() const
{
    QDomDocument doc;
    QFile file(m_ioParameter.inputFile);

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        qDebug() << "can't open file";
        return std::make_pair(Translations(), "Failed to open source!");
    }

    Translations translations;

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

            msg.source =
                nodeMsg.firstChildElement(QStringLiteral("source")).text();
            msg.translation =
                nodeMsg.firstChildElement(QStringLiteral("translation")).text();

            for (int k = 0; k < locations.size(); k++) {
                if (locations.at(k).nodeName() == "location") {
                    auto locMsg = locations.item(k);

                    msg.locations.emplace_back(wrapLocation(locMsg));
                }
            }
            context.messages.emplace_back(msg);
        }
        translations.emplace_back(context);
    }

    return std::make_pair(translations, "");
}

std::pair<QString, int> TsParser::wrapLocation(const QDomNode &node) const
{
    auto location = node.toElement();
    auto fn       = location.attributeNode(QStringLiteral("filename")).value();
    auto line     = location.attributeNode(QStringLiteral("line")).value();
    return std::make_pair(fn, line.toInt());
}
