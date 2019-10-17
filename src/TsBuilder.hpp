#pragma once

#include "TranslationObject.hpp"

class TsBuilder
{
  public:
    void build(const std::string &output_filename, Translations trs) const;
};
