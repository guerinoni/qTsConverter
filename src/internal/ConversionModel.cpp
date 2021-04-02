#include "ConversionModel.hpp"

#include "ConverterFactory.hpp"

#include <QDesktopServices>
#include <QUrl>
#include <algorithm>

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

void ConversionModel::clearInput()
{
    m_input.clear();
}

void ConversionModel::addInput(QString value)
{
    m_input.push_back(value);

    if (m_input.size() == 1) {
        m_sourceMsg = m_input.front();
        emit sourceMsgChanged();
        return;
    }

    if (m_input.size() > 1 && !inputHaveSameExtension()) {
        m_sourceMsg = "source files should have same extension";
        emit sourceMsgChanged();
        return;
    }

    m_sourceMsg = QString::number(m_input.size()) + " files selected";
    emit sourceMsgChanged();
}

QString ConversionModel::setOutput(const QString &value)
{
    m_output = value;
    QString temp =
        m_output.right(m_output.length() - 1 - m_output.lastIndexOf("/"));

    if (!temp.contains(QRegExp("\\S+\\.\\S+"))) {
        if (currentIndex == ConverterFactory::Ts2Xlsx) {
            m_output += ".xlsx";
        } else if (currentIndex == ConverterFactory::Ts2Csv) {
            m_output += ".csv";
        } else if (currentIndex != ConverterFactory::Dummy) {
            m_output += ".ts";
        }
    }

    deduceInputOutput();
    return m_output;
}

QStringList ConversionModel::getSaveFT()
{
    if (currentIndex == ConverterFactory::Csv2Ts ||
        currentIndex == ConverterFactory::Xlsx2Ts) {
        return QStringList({ "Translation files (*.ts)" });
    }

    if (currentIndex == ConverterFactory::Ts2Csv) {
        return QStringList({ "CSV files (*.csv)" });
    }

    if (currentIndex == ConverterFactory::Ts2Xlsx) {
        return QStringList({ "Excel files (*.xls, *.xlsx)" });
    }

    return QStringList({ "All files (*)" });
}

QStringList ConversionModel::getLoadFT()
{
    if (currentIndex == ConverterFactory::Ts2Csv ||
        currentIndex == ConverterFactory::Ts2Xlsx) {
        return QStringList({ "Translation files (*.ts)" });
    }

    if (currentIndex == ConverterFactory::Csv2Ts) {
        return QStringList({ "CSV files (*.csv)" });
    }

    if (currentIndex == ConverterFactory::Xlsx2Ts) {
        return QStringList({ "Excel files (*.xls, *.xlsx)" });
    }

    return QStringList({ "All files (*)" });
}

void ConversionModel::deduceInputOutput() noexcept
{
    if (m_input.isEmpty() || m_output.isEmpty()) {
        return;
    }

    if (m_input.endsWith(QStringLiteral(".ts"))) {
        if (m_output.endsWith(QStringLiteral(".csv"))) {
            currentIndex = ConverterFactory::Ts2Csv;
        }

        if (m_output.endsWith(QStringLiteral(".xls")) ||
            m_output.endsWith(QStringLiteral(".xlsx"))) {
            currentIndex = ConverterFactory::Ts2Xlsx;
        }
    } else if (m_input.endsWith(QStringLiteral(".csv"))) {
        if (m_output.endsWith(QStringLiteral(".ts"))) {
            currentIndex = ConverterFactory::Csv2Ts;
        }
    } else if (m_input.endsWith(QStringLiteral(".xls")) ||
               m_input.endsWith(QStringLiteral(".xlsx"))) {
        if (m_output.endsWith(QStringLiteral(".ts"))) {
            currentIndex = ConverterFactory::Xlsx2Ts;
        }
    }

    Q_EMIT setComboBoxIndex(currentIndex);
}

bool ConversionModel::inputHaveSameExtension() noexcept
{
    const auto extension = m_input.first().split(".")[1];
    return std::all_of(m_input.cbegin(), m_input.cend(), [&](const auto &s) {
        return s.split(".")[1] == extension;
    });
}

void ConversionModel::setIndex(const int &newIndex)
{
    currentIndex = newIndex;
}

void ConversionModel::openOutput()
{
    QString replaced = m_output;
    replaced.replace(0, 7, "");
    QDesktopServices::openUrl(QUrl::fromLocalFile(replaced));
}

void ConversionModel::openOutputFolder()
{
    QString replaced = m_output;
    replaced.replace(0, 7, "");
    int pos = replaced.lastIndexOf(QRegExp("/.*"));
    replaced.replace(pos, replaced.length() - pos, "");
    QDesktopServices::openUrl(QUrl::fromLocalFile(replaced));
}

QString ConversionModel::sourceMsg() const
{
    return m_sourceMsg;
}
