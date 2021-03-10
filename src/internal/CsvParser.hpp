#pragma once

#include "Parser.hpp"

class CsvParser : public Parser
{
  public:
    CsvParser() = default;
    explicit CsvParser(InOutParameter parameter);
    CsvParser(const CsvParser &) = delete;
    CsvParser(CsvParser &&)      = delete;
    ~CsvParser() override        = default;

    CsvParser &operator=(const CsvParser &) = delete;
    CsvParser &operator=(CsvParser &&) = delete;

    std::pair<Translations, QString> parse() const override;

  private:
    static std::pair<QString, int> decodeLocation(const QString &str);
    static void removeEmptyFrontBack(QList<QStringList> &list);
    void splitByRow(QList<QStringList> &list) const;
    static void removeQuote(QList<QStringList> &list);
    const int m_minimumSize{ 4 };
    static bool isLocation(const QString &value);

    const int kNameIndex{ 0 };
    const int kSourceIndex{ 1 };
    const int kTranslationIndex{ 2 };
    const int kLocationsIndex{ 3 };
    const int kRowSize{ 8 };
};
