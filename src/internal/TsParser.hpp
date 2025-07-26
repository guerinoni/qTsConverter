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

    Result parse() const override;

  private:
    static std::pair<QString, QString> wrapLocation(const QDomNode &node);
};
