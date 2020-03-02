#include "ConverterGuiProxy.hpp"

#include <QDebug>

ConverterGuiProxy::ConverterGuiProxy(QObject *parent) : QObject(parent) {}

void ConverterGuiProxy::convert(QConversionType type, QString input,
                                QString output, QString field_separator,
                                QString string_separator)
{
    input.remove("file://");
    output.remove("file://");
    auto converter = ConverterFactory::make_converter(
        static_cast<ConverterFactory::ConversionType>(type),
        input.toStdString(), output.toStdString(),
        field_separator.toStdString(), string_separator.toStdString());

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

static_assert(ConverterGuiProxy::QConversionType::Dummy ==
                  ConverterFactory::ConversionType::Dummy,
              "enum proxy QConversionType is different than ConversionType");
