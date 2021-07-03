#include "CliRunner.hpp"

#include <QtDebug>

CliRunner::CliRunner(QStringList &&args) : m_args{ args } {}

void CliRunner::run()
{
    if (m_args.size() < 2) {
        qCritical() << "error, only 1 parameter passed as arg.";
        return;
    }
}
