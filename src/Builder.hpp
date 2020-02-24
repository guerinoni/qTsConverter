#pragma once

#include "InOutParameter.hpp"
#include "TranslationObject.hpp"

class Builder
{
  public:
    explicit Builder(InOutParameter parameter);

    virtual void build(Translations &&trs) const = 0;

  protected:
    InOutParameter m_ioParameter;
};
