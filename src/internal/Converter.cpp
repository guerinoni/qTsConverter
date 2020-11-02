#include "Converter.hpp"

Converter::Converter(std::unique_ptr<Parser> parser,
                     std::unique_ptr<Builder> builder) :
    m_parser{ std::move(parser) },
    m_builder{ std::move(builder) }
{
}

Converter::CoversionResult Converter::process() const
{
    const auto result = m_parser->parse();
    if (result.first.empty()) {
        return CoversionResult(false, QStringLiteral("Failed to parse source!"),
                               result.second);
    }

    if (m_builder->build(result.first)) {
        return CoversionResult(true, QStringLiteral("Conversion successfull!"),
                               {});
    } else {
        return CoversionResult(false, QStringLiteral("Conversion failed!"), {});
    }
}
