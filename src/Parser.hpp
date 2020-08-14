#pragma once

#include "InOutParameter.hpp"
#include "TranslationObject.hpp"

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

    virtual std::pair<Translations, QString> parse() const = 0;

  protected:
    InOutParameter m_ioParameter;
};
