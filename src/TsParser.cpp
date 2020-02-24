#include "TsParser.hpp"

#include <QFile>
#include <QtXml>

Translations TsParser::parse(const std::string &filename) const
{
    QDomDocument doc;
    QFile file(filename.c_str());

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        qDebug() << "can't open file";
        return {};
    }

    Translations translations;

    auto contexts = doc.elementsByTagName("context");
    for (int i = 0; i < contexts.size(); ++i) {
        auto node = contexts.item(i);
        TranslationContext context;
        context.name = node.firstChildElement("name").text();
        auto msgs    = node.childNodes();
        for (auto j = 0; j < msgs.size(); j++) {
            auto node = msgs.item(j);

            if (node.nodeName() != "message") {
                continue;
            }

            TranslationMessage msg;
            msg.source      = node.firstChildElement("source").text();
            msg.translation = node.firstChildElement("translation").text();
            msg.locations.emplace_back(wrapLocation(node));
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
