#pragma once

#include <QStringList>

class CliRunner
{
  public:
    CliRunner() = default;
    explicit CliRunner(QStringList &&args);
    CliRunner(const CliRunner &) = delete;
    CliRunner(CliRunner &&)      = delete;
    ~CliRunner()                 = default;

    int run();

  private:
    QStringList m_args;

    static QString getSuffix(const QString &filepath);
};
