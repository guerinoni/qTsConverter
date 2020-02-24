#include "Converter.hpp"

Converter::Converter(std::unique_ptr<Parser> parser,
                     std::unique_ptr<Builder> builder) :
    m_parser{ std::move(parser) },
    m_builder{ std::move(builder) }
{
}

void Converter::process() const
{
    m_builder->build(m_parser->parse());
}
