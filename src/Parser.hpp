#pragma once

#include "InOutParameter.hpp"
#include "TranslationObject.hpp"

class Parser
{
  public:
    explicit Parser(InOutParameter parameter);

    virtual std::pair<Translations, QString> parse() const = 0;

  protected:
    InOutParameter m_ioParameter;
};
