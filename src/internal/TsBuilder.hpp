#pragma once

#include "Builder.hpp"

class QFile;

class TsBuilder : public Builder
{
  public:
    TsBuilder() = default;
    explicit TsBuilder(InOutParameter parameter);
    TsBuilder(const TsBuilder &) = delete;
    TsBuilder(TsBuilder &&)      = delete;
    ~TsBuilder() override        = default;

    TsBuilder operator=(const TsBuilder &) = delete;
    TsBuilder operator=(TsBuilder &&) = delete;

    bool build(const Translations &trs) const override;

  private:
    static void removeSlashInDoctype(QFile *f);
};
