#pragma once

#include "InOutParameter.hpp"
#include "TranslationObject.hpp"

class Parser
{
  public:
    explicit Parser(InOutParameter parameter);

    virtual Translations parse() const = 0;

  protected:
    InOutParameter m_ioParameter;
};
