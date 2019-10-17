#include "Csv2TsConverter.hpp"

Csv2TsConverter::Csv2TsConverter(const std::string &input,
                                 const std::string &output) :
    Converter{ input, output }
{
}

void Csv2TsConverter::process() const
{
    if (input_.empty() || output_.empty()) {
        return;
    }

    auto trs = parser_.parse(input_);
    builder_.build(output_ + "/output.ts", trs);
}
