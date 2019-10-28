#include "Ts2CsvConverter.hpp"

#include "CsvBuilder.hpp"

Ts2CsvConverter::Ts2CsvConverter(const std::string &input,
                                 const std::string &output,
                                 const std::string &field_sep,
                                 const std::string &string_sep) :
    Converter{ input, output }
{
    builder_ =
        std::make_shared<CsvBuilder>(CsvProperty{ field_sep, string_sep });
}

void Ts2CsvConverter::process() const
{
    if (input_.empty() || output_.empty()) {
        return;
    }

    auto trs = parser_.parse(input_);
    builder_->build(output_ + "/output.csv", trs);
}
