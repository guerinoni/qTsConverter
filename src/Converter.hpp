#pragma once

#include "Builder.hpp"
#include "InOutParameter.hpp"
#include "Parser.hpp"

#include <memory>

class Converter
{
  public:
    explicit Converter(std::unique_ptr<Parser> parser,
                       std::unique_ptr<Builder> builder);

    struct CoversionResult {
        CoversionResult(bool s, const QString &msg,
                        const QString &detailedMsg) :
            success(s),
            message(msg), detailedMessage(detailedMsg)
        {
        }

        bool success;
        QString message;
        QString detailedMessage;
    };

    virtual CoversionResult process() const;

  private:
    std::unique_ptr<Parser> m_parser;
    std::unique_ptr<Builder> m_builder;
};
