#include "Converter.hpp"

Converter::Converter(const std::string &inputFile,
                     const std::string &outputDir) :
    m_inputFile{ inputFile },
    m_outputDir{ outputDir }
{
}

void Converter::process() const {}
