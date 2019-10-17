#include "TsBuilder.hpp"

#include <QtXml>

void TsBuilder::build(const std::string &output_filename,
                      Translations trs) const
{
    QXmlStreamWriter writer;
    QFile output(output_filename.c_str());
    if (!output.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "can't open file" << output.fileName();
        return;
    }

    writer.setDevice(&output);

    writer.writeStartDocument();
    writer.writeStartElement("TS");
    writer.writeEndElement();
    writer.writeEndDocument();

    //    auto root    = doc.allocate_node(rapidxml::node_element, "TS");
    //    const auto v = doc.allocate_string(pod.version.c_str());
    //    root->append_attribute(doc.allocate_attribute("version", v));
    //    const auto l = doc.allocate_string(pod.language.c_str());
    //    root->append_attribute(doc.allocate_attribute("language", l));
    //    doc.append_node(root);

    //    for (const auto &d : pod) {
    //        auto node = doc.allocate_node(rapidxml::node_element, "context");
    //        auto name =
    //            doc.allocate_node(rapidxml::node_element, "name",
    //            d.name.c_str());
    //        node->append_node(name);
    //        for (const auto &m : d.translations) {
    //            auto mex = doc.allocate_node(rapidxml::node_element,
    //            "message"); for (const auto &loc : m.locations) {
    //                const auto l =
    //                    doc.allocate_node(rapidxml::node_element, "location");
    //                auto str = doc.allocate_string(loc.path.c_str());
    //                l->append_attribute(doc.allocate_attribute("filename",
    //                str)); auto line =
    //                    doc.allocate_string(std::to_string(loc.line).c_str());
    //                l->append_attribute(doc.allocate_attribute("line", line));
    //                mex->append_node(l);
    //            }
    //            const auto s1 = doc.allocate_string(m.source.c_str());
    //            auto source =
    //                doc.allocate_node(rapidxml::node_element, "source", s1);
    //            const auto s2 = doc.allocate_string(m.tr.c_str());
    //            auto tr =
    //                doc.allocate_node(rapidxml::node_element, "translation",
    //                s2);
    //            mex->append_node(source);
    //            mex->append_node(tr);
    //            node->append_node(mex);
    //        }
    //        root->append_node(node);
    //    }

    //    std::ostringstream oss;
    //    oss << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    //    oss << "<!DOCTYPE TS>\n";
    //    oss << doc;
    //    doc.clear();
    //    return oss;
}
