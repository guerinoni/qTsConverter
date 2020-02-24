#pragma once

#include "ConverterFactory.hpp"

#include <QObject>

class ConverterGuiProxy : public QObject
{
    Q_OBJECT

  public:
    explicit ConverterGuiProxy(QObject *parent = nullptr);

    enum QConversionType {
        Ts2Csv  = ConverterFactory::Ts2Csv,
        Csv2Ts  = ConverterFactory::Csv2Ts,
        Ts2Xlsx = ConverterFactory::Ts2Xlsx,
        Dummy
    };
    Q_ENUM(QConversionType)

  public slots:
    void convert(QConversionType type, QString input, QString output,
                 QString field_separator, QString string_separator);
};
