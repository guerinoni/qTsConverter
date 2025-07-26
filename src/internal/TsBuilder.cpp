#include "TsBuilder.hpp"

#include <QDomDocument>
#include <QFile>
#include <QXmlStreamWriter>
#include <QtDebug>

TsBuilder::TsBuilder(InOutParameter parameter) : Builder{ std::move(parameter) }
{
    if (!m_ioParameter.outputFile.endsWith("ts")) {
        m_ioParameter.outputFile += ".ts";
    }
}

auto TsBuilder::build(const Result &res) const -> bool
{
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
    if (res.root.sourcelanguage != "") {
        s.writeAttribute("sourcelanguage", res.root.sourcelanguage);
    }
    if (res.root.language != "") {
        s.writeAttribute("language", res.root.language);
    }

    for (const auto &ctxs : res.translantions) {
        s.writeStartElement("context");
        s.writeTextElement("name", ctxs.name);

        for (const auto &msg : ctxs.messages) {
            s.writeStartElement("message");
            if (msg.identifier != "") {
                s.writeAttribute("id", msg.identifier);
            }

            for (const std::pair<QString, QString> &loc : msg.locations) {
                s.writeEmptyElement("location");
                if (!loc.first.isEmpty())
                    s.writeAttribute("filename", loc.first);

                if (!loc.second.isEmpty())
                    s.writeAttribute("line", loc.second);
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
                s.writeAttribute("type", msg.translationtype);
            }
            s.writeCharacters(msg.translation);
            s.writeEndElement();

            s.writeEndElement(); // message
        }
        s.writeEndElement(); // context
    }

    s.writeEndDocument();

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
