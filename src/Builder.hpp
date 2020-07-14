#pragma once

#include "InOutParameter.hpp"
#include "TranslationObject.hpp"

class Builder
{
  public:
    Builder() = default;
    explicit Builder(InOutParameter parameter);
    Builder(const Builder &) = delete;
    Builder(Builder &&)      = delete;
    virtual ~Builder()       = default;

    Builder &operator=(const Builder &) = delete;
    Builder &operator=(Builder &&) = delete;

    virtual bool build(const Translations &trs) const = 0;

  protected:
    InOutParameter m_ioParameter;
};
