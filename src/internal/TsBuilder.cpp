#include "TsBuilder.hpp"

#include <QFile>
#include <QXmlStreamWriter>
#include <QtDebug>
#include <QDomDocument>

TsBuilder::TsBuilder(InOutParameter parameter) : Builder{ std::move(parameter) }
{
    if (!m_ioParameter.outputFile.endsWith("ts")) {
        m_ioParameter.outputFile += ".ts";
    }
}

auto TsBuilder::build(const Result &res) const -> bool
{

    QDomDocument doc;
    QDomProcessingInstruction h = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    doc.appendChild(h);

    QDomElement elem = doc.createElement("!DOCTYPE TS");
    doc.appendChild(elem);

    QDomElement root = doc.createElement("TS");
    if (res.root.language != "") {
        root.setAttribute("language", res.root.language);
    }
    if (res.root.sourcelanguage != "") {
        root.setAttribute("sourcelanguage", res.root.sourcelanguage);
    }
    if (res.root.tsVersion != "") {
        root.setAttribute("version", res.root.tsVersion);
    }
    doc.appendChild(root);

    for (const auto &ctxs : res.translantions) {

        QDomElement context = doc.createElement("context");
        root.appendChild(context);

        elem = doc.createElement("name");
        context.appendChild(elem);
        QDomText text = doc.createTextNode(ctxs.name);
        elem.appendChild(text);

        for (const auto &msg : ctxs.messages) {

            QDomElement message = doc.createElement("message");
            context.appendChild(message);

            for (const auto &loc : msg.locations) {
                elem = doc.createElement("location");
                elem.setAttribute("filename", loc.first);
                elem.setAttribute("line", QString::number(loc.second));
                message.appendChild(elem);
            }

            elem = doc.createElement("source");
            message.appendChild(elem);
            text = doc.createTextNode(msg.source);
            elem.appendChild(text);

            if (msg.comment != "") {
                elem = doc.createElement("comment");
                message.appendChild(elem);
                text = doc.createTextNode(msg.comment);
                elem.appendChild(text);
            }

            if (msg.extracomment != "") {
                elem = doc.createElement("extracomment");
                message.appendChild(elem);
                text = doc.createTextNode(msg.extracomment);
                elem.appendChild(text);
            }

            if (msg.translatorcomment != "") {        
                elem = doc.createElement("translatorcomment");
                message.appendChild(elem);
                text = doc.createTextNode(msg.translatorcomment);
                elem.appendChild(text);
            }
            
            elem = doc.createElement("translation");
            if (msg.translationtype != "") {
                elem.setAttribute("type", msg.translationtype);
            }
            message.appendChild(elem);
            text = doc.createTextNode(msg.translation);
            elem.appendChild(text);
        }
    }

    QFile output(m_ioParameter.outputFile);
    if (!output.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning() << "can't open file" << output.fileName();
        return false;
    }
    else {
        QTextStream stream(&output);
        stream << doc.toString();
    }    
    
    output.close();
    removeSlashInDoctype(&output);
    return true;
}

void TsBuilder::removeSlashInDoctype(QFile *f)
{
    f->open(QIODevice::ReadWrite);
    auto fileData = f->readAll();
    QString text(fileData);
    text.replace("!DOCTYPE TS/", "!DOCTYPE TS");
    f->seek(0);
    f->write(text.toUtf8());
    f->close();
}
