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
    if (result.first.empty()) {
        return CoversionResult(false, QStringLiteral("Failed to parse source!"),
                               result.second);
    }

    const auto ok = m_builder->build(result.first);

    return ok ? CoversionResult(true, QStringLiteral("Conversion successfull!"),
                                {})
              : CoversionResult(false, QStringLiteral("Conversion failed!"),
                                {});
}
