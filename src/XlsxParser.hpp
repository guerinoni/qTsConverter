#pragma once

#include "Parser.hpp"

class QDomNode;

class XlsxParser : public Parser
{
  public:
    XlsxParser() = default;
    explicit XlsxParser(InOutParameter &&parameter);
    XlsxParser(const XlsxParser &) = delete;
    XlsxParser(XlsxParser &&)      = delete;
    virtual ~XlsxParser()          = default;

    XlsxParser &operator=(const XlsxParser &) = delete;
    XlsxParser &operator=(XlsxParser &&) = delete;

    std::pair<Translations, QString> parse() const override;
};
