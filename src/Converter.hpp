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

    virtual void process() const;

  private:
    std::unique_ptr<Parser> m_parser;
    std::unique_ptr<Builder> m_builder;
};
