#include <QtTest>

class tst_Ts2Csv : public QObject
{
    Q_OBJECT

  private slots:
    void cleanup();

    void checkScenario1();

  private:
    const std::string m_outputFile{ FILESPATH + std::string("/output.csv") };
};
