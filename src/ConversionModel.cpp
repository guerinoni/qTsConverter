#include "ConversionModel.hpp"

#include "ConverterFactory.hpp"

ConversionModel::ConversionModel(QObject *parent) :
    QAbstractListModel(parent), m_conversions{ "TS => CSV", "CSV => TS",
                                               "TS => XLSX", "XLSX => TS",
                                               "Error" }
{
}

int ConversionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_conversions.size();
}

QVariant ConversionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (role == Roles::String) {
        return m_conversions.at(index.row());
    }

    return {};
}

QHash<int, QByteArray> ConversionModel::roleNames() const
{
    return { { Roles::String, "stringRole" } };
}

void ConversionModel::setInput(const QString &value)
{
    m_input = value;
    deduceInputOutput();
}

void ConversionModel::setOutput(const QString &value)
{
    m_output = value;
    deduceInputOutput();
}

void ConversionModel::deduceInputOutput() noexcept
{
    if (m_input.isEmpty() || m_output.isEmpty()) {
        return;
    }

    if (m_input.endsWith(".ts")) {
        if (m_output.endsWith(".csv")) {
            Q_EMIT setComboBoxIndex(ConverterFactory::Ts2Csv);
        }

        if (m_output.endsWith(".xls") || m_output.endsWith(".xlsx")) {
            Q_EMIT setComboBoxIndex(ConverterFactory::Ts2Xlsx);
        }
    }

    if (m_input.endsWith(".csv")) {
        if (m_output.endsWith(".ts")) {
            Q_EMIT setComboBoxIndex(ConverterFactory::Csv2Ts);
        }
    }

    if (m_input.endsWith(".xls") || m_input.endsWith(".xlsx")) {
        if (m_output.endsWith(".ts")) {
            Q_EMIT setComboBoxIndex(ConverterFactory::Xlsx2Ts);
        }
    }
}
