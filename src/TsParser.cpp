#include "TsParser.hpp"

#include <QFile>
#include <QtXml>

TsParser::TsParser(InOutParameter parameter) : Parser{ parameter } {}

Translations TsParser::parse() const
{
    QDomDocument doc;
    QFile file(m_ioParameter.inputFile.c_str());

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        qDebug() << "can't open file";
        return {};
    }

    Translations translations;

    auto contexts = doc.elementsByTagName("context");
    for (int i = 0; i < contexts.size(); ++i) {
        auto nodeCtx = contexts.item(i);
        TranslationContext context;
        context.name = nodeCtx.firstChildElement("name").text();
        auto msgs    = nodeCtx.childNodes();
        for (auto j = 0; j < msgs.size(); j++) {
            auto nodeMsg = msgs.item(j);

            if (nodeMsg.nodeName() != "message") {
                continue;
            }

            TranslationMessage msg;
            msg.source      = nodeMsg.firstChildElement("source").text();
            msg.translation = nodeMsg.firstChildElement("translation").text();
            msg.locations.emplace_back(wrapLocation(nodeMsg));
            context.messages.emplace_back(msg);
        }

        translations.emplace_back(context);
    }

    return translations;
}

std::pair<QString, int> TsParser::wrapLocation(const QDomNode &node) const
{
    auto location = node.firstChildElement("location");
    auto fn       = location.attributeNode("filename").value();
    auto line     = location.attributeNode("line").value();
    return std::make_pair(fn, line.toInt());
}
