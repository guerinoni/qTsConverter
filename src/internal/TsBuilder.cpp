#include "TsBuilder.hpp"

#include <QFile>
#include <QXmlStreamWriter>
#include <QtDebug>

TsBuilder::TsBuilder(InOutParameter parameter) : Builder{ std::move(parameter) }
{
    if (!m_ioParameter.outputFile.endsWith("ts")) {
        m_ioParameter.outputFile += ".ts";
    }
}

bool TsBuilder::build(const Translations &trs) const
{
    QFile output(m_ioParameter.outputFile);
    if (!output.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning() << "can't open file" << output.fileName();
        return false;
    }

    QXmlStreamWriter s(&output);
    s.setAutoFormatting(true);
    s.setAutoFormattingIndent(2);
    s.writeStartDocument();

    s.writeEmptyElement("!DOCTYPE TS");
    s.writeStartElement("TS");
    s.writeAttribute("version", m_ioParameter.tsVersion);

    for (const auto &ctxs : trs) {
        s.writeStartElement("context");
        s.writeTextElement("name", ctxs.name);

        for (const auto &msg : ctxs.messages) {
            s.writeStartElement("message");

            for (const auto &loc : msg.locations) {
                s.writeEmptyElement("location");
                s.writeAttribute("line", QString::number(loc.second));
                s.writeAttribute("filename", loc.first);
            }

            s.writeTextElement("source", msg.source);
            s.writeTextElement("translation", msg.translation);
            s.writeEndElement(); // message
        }
        s.writeEndElement(); // context
    }

    s.writeEndDocument();
    output.close();
    removeSlashInDoctype(&output);
    return true;
}

void TsBuilder::removeSlashInDoctype(QFile *f) const
{
    f->open(QIODevice::ReadWrite);
    auto fileData = f->readAll();
    QString text(fileData);
    text.replace("!DOCTYPE TS/", "!DOCTYPE TS");
    f->seek(0);
    f->write(text.toUtf8());
    f->close();
}
