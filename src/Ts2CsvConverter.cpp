#include "Ts2CsvConverter.hpp"

Ts2CsvConverter::Ts2CsvConverter(const std::string &input,
                                 const std::string &output) :
    Converter{ input, output }
{
}

void Ts2CsvConverter::process() const
{
    if (input_.empty() || output_.empty()) {
        return;
    }

    auto trs = parser_.parse(input_);
    builder_.build(output_ + "/output.csv", trs);
}
