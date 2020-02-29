#pragma once

#include "Parser.hpp"

class QDomNode;

class XlsxParser : public Parser
{
  public:
    explicit XlsxParser(InOutParameter parameter);

    Translations parse() const override;
};
