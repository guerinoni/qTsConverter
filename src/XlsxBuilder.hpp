#pragma once

#include "TranslationObject.hpp"

class XlsxBuilder
{
  public:
    void build(const std::string &output_filename, Translations trs) const;
};
