#pragma once

#include "Parser.hpp"

class QDomNode;

class TsParser : public Parser
{
  public:
    TsParser() = default;
    explicit TsParser(InOutParameter &&parameter);
    TsParser(const TsParser &) = delete;
    TsParser(TsParser &&)      = delete;
    ~TsParser() override       = default;

    TsParser &operator=(const TsParser &) = delete;
    TsParser &operator=(TsParser &&) = delete;

    std::pair<Translations, QString> parse() const override;

  private:
    std::pair<QString, int> wrapLocation(const QDomNode &node) const;
};
