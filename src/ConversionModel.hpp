#pragma once

#include <QAbstractListModel>

class ConversionModel final : public QAbstractListModel
{
    Q_OBJECT

  public:
    explicit ConversionModel(QObject *parent = nullptr);

    enum Roles { String = Qt::UserRole + 1 };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setInput(const QString &value);
    Q_INVOKABLE QString setOutput(const QString &value);

    Q_INVOKABLE QStringList getLoadFT();
    Q_INVOKABLE QStringList getSaveFT();

    Q_INVOKABLE void setIndex(const int &newIndex);

    Q_INVOKABLE void openOutput();
    Q_INVOKABLE void openOutputFolder();

  Q_SIGNALS:
    void setComboBoxIndex(int index);

  private:
    QVector<QString> m_conversions;
    QString m_input;
    QString m_output;

    void deduceInputOutput() noexcept;
    int currentIndex = 4;
};
