#pragma once

#include "Parser.hpp"

class QDomNode;

class XlsxParser : public Parser
{
  public:
    explicit XlsxParser(InOutParameter parameter);

    std::pair<Translations, QString> parse() const override;
};
