#include "CliRunner.hpp"

#include "ConverterFactory.hpp"

#include <QDir>
#include <QtDebug>

CliRunner::CliRunner(QStringList &&args) : m_args{ args } {}

auto CliRunner::run() -> int
{
    if (m_args.size() < 2) {
        qCritical() << "error, only 1 parameter passed as arg.";
        return 1;
    }

    const auto input = m_args.at(0);
    auto output      = m_args.at(1);

    if (output.startsWith("./")) {
        output = QDir::toNativeSeparators(QDir::currentPath() + "/" + output);
    }

    using CF        = ConverterFactory;
    const auto type = CF::fromString(getSuffix(input), getSuffix(output));
    auto converter  = CF::make_converter(type, input, output, ";", "\"", "2.1");

    const auto tmpResult = converter->process();
    qInfo() << tmpResult.success << tmpResult.message
            << tmpResult.detailedMessage;
    return static_cast<int>(tmpResult.success);
}

auto CliRunner::getSuffix(const QString &filepath) -> QString
{
    const auto dotPoint = filepath.lastIndexOf('.');
    return filepath.right(filepath.size() - dotPoint);
}
