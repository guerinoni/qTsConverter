#include "TsBuilder.hpp"

#include <QFile>
#include <QXmlStreamWriter>
#include <QtDebug>
#include <QDomDocument>

#undef QDOMONLY

TsBuilder::TsBuilder(InOutParameter parameter) : Builder{ std::move(parameter) }
{
    if (!m_ioParameter.outputFile.endsWith("ts")) {
        m_ioParameter.outputFile += ".ts";
    }
}

auto TsBuilder::build(const Result &res) const -> bool
{
#ifdef QDOMONLY
    qSetGlobalQHashSeed(0);

    QDomDocument doc;
    QDomProcessingInstruction h = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    doc.appendChild(h);

    QDomElement elem = doc.createElement("!DOCTYPE TS");
    doc.appendChild(elem);

    QDomElement root = doc.createElement("TS");
    if (res.root.tsVersion != "") {
        root.setAttribute("version", res.root.tsVersion);
    }
    if (res.root.sourcelanguage != "") {
        root.setAttribute("sourcelanguage", res.root.sourcelanguage);
    }
    if (res.root.language != "") {
        root.setAttribute("language", res.root.language);
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
            if (msg.identifier != "") {
                message.setAttribute("id", msg.identifier);
            }
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
#else
    QFile output(m_ioParameter.outputFile);
    if (!output.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning() << "can't open file" << output.fileName();
        return false;
    }

    QXmlStreamWriter s(&output);

    s.setAutoFormatting(true);
    s.setAutoFormattingIndent(4);
    s.writeStartDocument();

    s.writeEmptyElement("!DOCTYPE TS");
    
    // Create root element with attributes
    s.writeStartElement("TS");
    s.writeAttribute("version", res.root.tsVersion);
    if (res.root.sourcelanguage != "" ) {
        s.writeAttribute("sourcelanguage", res.root.sourcelanguage);
    }
    if (res.root.language != "" ) {
        s.writeAttribute("language", res.root.language);
    }

    for (const auto &ctxs : res.translantions) {
        s.writeStartElement("context");
        s.writeTextElement("name", ctxs.name);

        for (const auto &msg : ctxs.messages) {
            s.writeStartElement("message");
            if (msg.identifier != "" ) {
                s.writeAttribute("id", msg.identifier);
            }

            for (const auto &loc : msg.locations) {
                s.writeEmptyElement("location");
                s.writeAttribute("filename", loc.first);
                s.writeAttribute("line", QString::number(loc.second));
            }

            s.writeTextElement("source", msg.source);
            if (msg.comment != "") {
                s.writeTextElement("comment", msg.comment);
            }
            if (msg.extracomment != "") {
                s.writeTextElement("extracomment", msg.extracomment);
            }
            if (msg.translatorcomment != "") {
                s.writeTextElement("translatorcomment", msg.translatorcomment);
            }
            
            s.writeStartElement("translation");
            if (msg.translationtype != "") {
                s.writeAttribute("type",msg.translationtype);
            }
            s.writeCharacters(msg.translation);
            s.writeEndElement();

            s.writeEndElement(); // message
        }
        s.writeEndElement(); // context
    }

    s.writeEndDocument();
#endif

    output.close();
    removeSlashInDoctype(&output);

    qSetGlobalQHashSeed(-1);

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
