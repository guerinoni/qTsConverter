#pragma once

#include "Parser.hpp"

class CsvParser : public Parser
{
  public:
    CsvParser() = default;
    explicit CsvParser(InOutParameter parameter);
    CsvParser(const CsvParser &) = delete;
    CsvParser(CsvParser &&)      = delete;

    virtual ~CsvParser() = default;

    CsvParser &operator=(const CsvParser &) = delete;
    CsvParser &operator=(CsvParser &&) = delete;

    std::pair<Translations, QString> parse() const override;

  private:
    std::pair<QString, int> decodeLocation(const QString &str) const;
    void removeEmptyFrontBack(QList<QStringList> &list) const;
    void splitMergedString(QList<QStringList> &list) const;
    void splitByRow(QList<QStringList> &list) const;
    void removeQuote(QList<QStringList> &list) const;
};
