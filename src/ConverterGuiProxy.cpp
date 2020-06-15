#include "ConverterGuiProxy.hpp"

#include <QDebug>

ConverterGuiProxy::ConverterGuiProxy(QObject *parent) : QObject(parent) {}

void ConverterGuiProxy::convert(QConversionType type, QString input,
                                QString output, const QString &fieldSeparator,
                                const QString &stringSeparator,
                                const QString &tsVersion)
{
    // Remove file:// on linux and file:/// on windows
    input  = QUrl::fromUserInput(input).toLocalFile();
    output = QUrl::fromUserInput(output).toLocalFile();

    auto converter = ConverterFactory::make_converter(
        static_cast<ConverterFactory::ConversionType>(type), input, output,
        fieldSeparator, stringSeparator, tsVersion);

    const auto results = converter->process();
    setConversionInfo(results.success, results.message,
                      results.detailedMessage);
}

bool ConverterGuiProxy::convSuccessfull() const
{
    return m_convSuccessfull;
}

QString ConverterGuiProxy::convMsg() const
{
    return m_convMsg;
}

QString ConverterGuiProxy::detailedConvMsg() const
{
    return m_detailedConvMsg;
}

void ConverterGuiProxy::setConversionInfo(bool convSuccessfull,
                                          const QString &errorMsg,
                                          const QString &detailedConvMsg)
{
    m_convSuccessfull = convSuccessfull;
    m_convMsg         = errorMsg;
    m_detailedConvMsg = detailedConvMsg;
    Q_EMIT conversionCompleted();
}

static_assert(static_cast<int>(ConverterGuiProxy::QConversionType::Dummy) ==
                  static_cast<int>(ConverterFactory::ConversionType::Dummy),
              "enum proxy QConversionType is different than ConversionType");
