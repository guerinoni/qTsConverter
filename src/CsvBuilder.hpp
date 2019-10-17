#pragma once

#include "TranslationObject.hpp"

class CsvBuilder
{
  public:
    void build(const std::string &output_filename, Translations trs) const;
};
