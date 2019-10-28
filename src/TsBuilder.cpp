#include "TsBuilder.hpp"

#include <QtXml>

void TsBuilder::build(const std::string &output_filename,
                      Translations trs) const
{
    QFile output(output_filename.c_str());
    if (!output.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "can't open file" << output.fileName();
        return;
    }

    QDomDocument doc("TS");

    auto root = doc.createElement("TS");
    root.setAttribute("version", "2.1");    // TODO: extract as parameter
    root.setAttribute("language", "en_US"); // TODO: extract as parameter

    for (const auto &tr : trs) {
        auto name = doc.createElement("name");
        name.appendChild(doc.createTextNode(tr.name));

        auto source = doc.createElement("source");
        source.appendChild(doc.createTextNode(tr.source));

        auto translation = doc.createElement("translation");
        translation.appendChild(doc.createTextNode(tr.translation));

        auto message = doc.createElement("message");
        message.appendChild(source);
        message.appendChild(translation);

        auto context = doc.createElement("context");
        context.appendChild(name);
        context.appendChild(message);
        root.appendChild(context);
    }

    doc.appendChild(root);

    QTextStream stream(&output);
    stream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    stream << doc.toString();
    output.close();
}
