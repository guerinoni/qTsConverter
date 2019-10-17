#pragma once

#include "TranslationObject.hpp"

class CsvParser
{
  public:
    Translations parse(const std::string &filename) const;
};
