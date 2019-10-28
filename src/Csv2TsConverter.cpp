#include "Csv2TsConverter.hpp"

#include "CsvParser.hpp"

Csv2TsConverter::Csv2TsConverter(const std::string &input,
                                 const std::string &output,
                                 const std::string &field_sep,
                                 const std::string &string_sep) :
    Converter{ input, output }
{
    parser_ = std::make_shared<CsvParser>(CsvProperty{ field_sep, string_sep });
}

void Csv2TsConverter::process() const
{
    if (input_.empty() || output_.empty()) {
        return;
    }

    auto trs = parser_->parse(input_);
    builder_.build(output_ + "/output.ts", trs);
}
