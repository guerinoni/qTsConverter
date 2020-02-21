#pragma once

#include <string>

class Converter
{
  public:
    explicit Converter(const std::string &inputFile,
                       const std::string &outputDir);
    Converter()                       = default;
    Converter(const Converter &other) = default;
    Converter(Converter &&other)      = default;
    virtual ~Converter()              = default;

    Converter &operator=(const Converter &other) = default;
    Converter &operator=(Converter &&other) = default;

    virtual void process() const;

  protected:
    std::string m_inputFile;
    std::string m_outputDir;
};
