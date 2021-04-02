#pragma once

#include <QAbstractListModel>

class ConversionModel final : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString sourceMsg READ sourceMsg NOTIFY sourceMsgChanged)

  public:
    ConversionModel() = delete;
    explicit ConversionModel(QObject *parent = nullptr);
    ConversionModel(const ConversionModel &) = delete;
    ConversionModel(ConversionModel &&)      = delete;
    ~ConversionModel() override              = default;

    ConversionModel &operator=(const ConversionModel &) = delete;
    ConversionModel &operator=(ConversionModel &&) = delete;

    enum Roles { String = Qt::UserRole + 1 };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void clearInput();
    Q_INVOKABLE void addInput(QString value);
    Q_INVOKABLE QString setOutput(const QString &value);

    Q_INVOKABLE QStringList getLoadFT();
    Q_INVOKABLE QStringList getSaveFT();

    Q_INVOKABLE void setIndex(const int &newIndex);

    Q_INVOKABLE void openOutput();
    Q_INVOKABLE void openOutputFolder();

    QString sourceMsg() const;

  signals:
    void setComboBoxIndex(int index);
    void sourceMsgChanged();

  private:
    QVector<QString> m_conversions;
    QList<QString> m_input;
    QString m_output;

    QString m_sourceMsg;

    void deduceInputOutput() noexcept;
    int currentIndex = 4;
};
