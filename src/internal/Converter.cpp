#include "Converter.hpp"

Converter::Converter(std::unique_ptr<Parser> parser,
                     std::unique_ptr<Builder> builder) :
    m_parser{ std::move(parser) },
    m_builder{ std::move(builder) }
{
}

auto Converter::process() const -> Converter::CoversionResult
{
    const auto result = m_parser->parse();
    if (!result.error.isEmpty()) {
        return CoversionResult(true, QStringLiteral("Failed to parse source!"),
                               result.error);
    }

    const auto ok = m_builder->build(result);

    return ok ? CoversionResult(false,
                                QStringLiteral("Conversion successfull!"), {})
              : CoversionResult(true, QStringLiteral("Conversion failed!"), {});
}
