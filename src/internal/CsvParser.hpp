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

    Result parse() const override;

  private:
    static std::pair<QString, QString> decodeLocation(const QString &str);
    static void removeEmptyFrontBack(QList<QStringList> &list);
    void splitByRow(QList<QStringList> &list) const;
    static void removeQuote(QList<QStringList> &list);
    const int m_minimumSize{ 4 };
    static bool isLocation(const QString &value);

    const int kNameIndex{ 0 };
    const int kIdIndex{ 1 };
    const int kSourceIndex{ 2 };
    const int kTranslationIndex{ 3 };
    const int kTranslationTypeIndex{ 4 };
    const int kCommentIndex{ 5 };
    const int kExtraCommentIndex{ 6 };
    const int kTranslatorCommentIndex{ 7 };
    const int kLocationsIndex{ 8 };
    const int kRowSize{ 8 };
};
