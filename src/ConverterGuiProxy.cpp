#include "ConverterGuiProxy.hpp"

#include <QDebug>

ConverterGuiProxy::ConverterGuiProxy(QObject *parent) : QObject(parent) {}

void ConverterGuiProxy::convert(QConversionType type, QString input,
                                QString output)
{
    input.remove("file://");
    output.remove("file://");
    auto converter = ConverterFactory::make_converter(
        static_cast<ConverterFactory::ConversionType>(type),
        input.toStdString(), output.toStdString());
    converter->process();
}

static_assert(ConverterGuiProxy::QConversionType::Dummy ==
                  ConverterFactory::ConversionType::Dummy,
              "enum proxy QConversionType is different than ConversionType");
