#include "Ts2XlsxConverter.hpp"

#include "XlsxBuilder.hpp"

Ts2XlsxConverter::Ts2XlsxConverter(const std::string &input,
                                   const std::string &output,
                                   const std::string &field_sep,
                                   const std::string &string_sep) :
    Converter{ input, output }
{
    m_builder = std::make_shared<XlsxBuilder>();
}

void Ts2XlsxConverter::process() const
{
    if (m_inputFile.empty() || m_outputDir.empty()) {
        return;
    }

    auto trs = m_parser.parse(m_inputFile);
    m_builder->build(m_outputDir + "/output.xlsx", trs);
}
