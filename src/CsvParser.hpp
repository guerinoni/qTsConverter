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

    std::pair<QString, int> decodeLocation(QString str) const;
};
