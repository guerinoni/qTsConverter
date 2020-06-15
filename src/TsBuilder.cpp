#include "TsBuilder.hpp"

#include <QtXml>

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
        qDebug() << "can't open file" << output.fileName();
        return false;
    }

    QDomDocument doc(QStringLiteral("TS"));

    auto root = doc.createElement(QStringLiteral("TS"));
    root.setAttribute(QStringLiteral("version"), m_ioParameter.tsVersion);

    for (const auto &ctxs : trs) {
        auto context = doc.createElement(QStringLiteral("context"));
        auto name    = doc.createElement(QStringLiteral("name"));
        name.appendChild(doc.createTextNode(ctxs.name));
        context.appendChild(name);

        for (const auto &msg : ctxs.messages) {
            auto message = doc.createElement(QStringLiteral("message"));
            for (const auto &loc : msg.locations) {
                auto location = doc.createElement(QStringLiteral("location"));
                location.setAttribute(QStringLiteral("line"), loc.second);
                location.setAttribute(QStringLiteral("filename"), loc.first);
                message.appendChild(location);
            }

            auto source = doc.createElement(QStringLiteral("source"));
            source.appendChild(doc.createTextNode(msg.source));
            message.appendChild(source);

            auto translation = doc.createElement(QStringLiteral("translation"));
            translation.appendChild(doc.createTextNode(msg.translation));
            message.appendChild(translation);
            context.appendChild(message);
        }

        root.appendChild(context);
    }

    doc.appendChild(root);
    doc.normalize();

    QTextStream stream(&output);
    stream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    stream << doc.toString(2);

    output.close();
    return true;
}
