#pragma once

#include "TranslationObject.hpp"

class QDomNode;

class TsParser
{
  public:
    Translations parse(const std::string &filename) const;

  private:
    std::pair<QString, int> wrapLocation(const QDomNode &node) const;
};
