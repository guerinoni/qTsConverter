#pragma once

#include <string>

class Converter
{
  public:
    explicit Converter(const std::string &input, const std::string &output);
    Converter()                       = default;
    Converter(const Converter &other) = default;
    Converter(Converter &&other)      = default;
    virtual ~Converter()              = default;

    Converter &operator=(const Converter &other) = default;
    Converter &operator=(Converter &&other) = default;

    virtual void process() const;

  protected:
    std::string input_;
    std::string output_;
};
