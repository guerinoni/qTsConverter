#include "Csv2TsConverter.hpp"

Csv2TsConverter::Csv2TsConverter(const std::string &input,
                                 const std::string &output,
                                 const std::string &field_sep,
                                 const std::string &string_sep) :
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
