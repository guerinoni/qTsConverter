#pragma once

#include "CsvProperty.hpp"
#include "TranslationObject.hpp"

class CsvBuilder
{
  public:
    explicit CsvBuilder(CsvProperty property);

    void build(const std::string &output_filename, Translations trs) const;

  private:
    CsvProperty property_;
};
