#include "ConverterGuiProxy.hpp"

#include <QDebug>

ConverterGuiProxy::ConverterGuiProxy(QObject *parent) : QObject(parent) {}

void ConverterGuiProxy::convert(QConversionType type, QString input,
                                QString output, QString field_separator,
                                QString string_separator)
{
    // Remove file:// on linux and file:/// on windows
    input  = QUrl::fromUserInput(input).toLocalFile();
    output = QUrl::fromUserInput(output).toLocalFile();

    qDebug() << input << output;
    auto converter = ConverterFactory::make_converter(
        static_cast<ConverterFactory::ConversionType>(type),
        input.toStdString(), output.toStdString(),
        field_separator.toStdString(), string_separator.toStdString());
    converter->process();
}

static_assert(ConverterGuiProxy::QConversionType::Dummy ==
                  ConverterFactory::ConversionType::Dummy,
              "enum proxy QConversionType is different than ConversionType");
