#pragma once

#include "TranslationObject.hpp"

class TsParser
{
  public:
    Translations parse(const std::string &filename) const;
};
