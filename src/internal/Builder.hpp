#pragma once

#include "Result.hpp"

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

    virtual bool build(const Result &res) const = 0;

  protected:
    InOutParameter m_ioParameter;
};
