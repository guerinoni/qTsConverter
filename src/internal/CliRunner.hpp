#pragma once

#include <QStringList>

class CliRunner
{
  public:
    CliRunner() = default;
    explicit CliRunner(QStringList &&args, bool noVersion, bool noLocation);
    CliRunner(const CliRunner &) = delete;
    CliRunner(CliRunner &&)      = delete;
    ~CliRunner()                 = default;

    int run();

  private:
    QStringList m_args;
    bool m_noVersion;
    bool m_noLocation;

    static QString getSuffix(const QString &filepath);
};
