#pragma once

#include "Result.hpp"

class Parser
{
  public:
    Parser() = default;
    explicit Parser(InOutParameter &&parameter);
    Parser(const Parser &) = delete;
    Parser(Parser &&)      = delete;
    virtual ~Parser()      = default;

    Parser &operator=(const Parser &) = delete;
    Parser &operator=(Parser &&) = delete;

    virtual Result parse() const = 0;

  protected:
    InOutParameter m_ioParameter;
};
