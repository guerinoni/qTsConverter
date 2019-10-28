#pragma once

#include "CsvProperty.hpp"
#include "TranslationObject.hpp"

class CsvParser
{
  public:
    explicit CsvParser(CsvProperty property);

    Translations parse(const std::string &filename) const;

  private:
    CsvProperty property_;
};
