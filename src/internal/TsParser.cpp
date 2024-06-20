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

    Header h;
    Translations translations;

/*
    // https://doc.qt.io/qt-6/linguist-ts-file-format.html
    // https://techbase.kde.org/Development/Tutorials/QtDOM_Tutorial#Loading_a_simple_XML_file_using_Qt_DOM
    // https://www.qtforum.de/viewtopic.php?t=15573
    // https://www.liquid-technologies.com/online-xsd-to-xml-converter
    //qDebug() << doc.toString();
 */
    QDomElement docElem = doc.documentElement();
    //qDebug() << docElem.tagName();
    h.tsVersion = docElem.attributeNode("version").value();
    h.language = docElem.attributeNode("language").value();
    h.sourcelanguage = docElem.attributeNode("sourcelanguage").value();
    
    //QDomAttr testAttr2 = docElem.attributeNode("language");
    //qDebug() << testAttr2.value();
    //h.language = testAttr2.value();
    
    //QDomAttr testAttr3 = docElem.attributeNode("sourcelanguage");
    //qDebug() << testAttr3.value();
    //h.sourcelanguage = testAttr3.value();

/*     auto e = doc.elementsByTagName(QStringLiteral("TS"));
    qDebug() << e.item(0).nodeName();
    qDebug() << e.item(1).nodeName();
    qDebug() << e.item(2).nodeName();

     QDomNode n = docElem.firstChild();
    
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
        }
        n = n.nextSibling();
    }
 */
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

    return Result{ "", std::move(translations), {}, std::move(h) };
}

auto TsParser::wrapLocation(const QDomNode &node) -> std::pair<QString, int>
{
    auto location = node.toElement();
    auto fn       = location.attributeNode(QStringLiteral("filename")).value();
    auto line     = location.attributeNode(QStringLiteral("line")).value();
    return std::make_pair(fn, line.toInt());
}
