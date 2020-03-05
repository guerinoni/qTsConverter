#pragma once

#include "Parser.hpp"

class CsvParser : public Parser
{
  public:
    explicit CsvParser(InOutParameter parameter);

    std::pair<Translations, QString> parse() const override;

  private:
    std::pair<QString, int> decodeLocation(QString str) const;
    void removeEmptyFrontBack(QList<QStringList> &list) const;
    void splitMergedString(QList<QStringList> &list) const;
    void splitByRow(QList<QStringList> &list) const;
    void removeQuote(QList<QStringList> &list) const;
};
