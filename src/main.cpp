#include "ConversionModel.hpp"
#include "ConverterGuiProxy.hpp"

#include <QApplication>
#include <QFontDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef Q_OS_WIN
    QQuickWindow::setTextRenderType(
        QQuickWindow::TextRenderType::NativeTextRendering);
#endif

    QGuiApplication app(argc, argv);
    QApplication::setOrganizationName(QStringLiteral("Federico Guerinoni"));
    QApplication::setOrganizationDomain(QStringLiteral("Federico Guerinoni"));
    QApplication::setApplicationName(QStringLiteral("qTsConverter"));
    QApplication::setWindowIcon(QIcon(":/assets/logos/profile.png"));

    QFontDatabase::addApplicationFont(
        QStringLiteral(":/assets/fonts/Roboto-Light.ttf"));
    QFontDatabase::addApplicationFont(
        QStringLiteral(":/assets/fonts/Roboto-Regular.ttf"));

    QQmlApplicationEngine engine;

    ConversionModel cm(nullptr);
    engine.rootContext()->setContextProperty(QStringLiteral("conversionModel"),
                                             &cm);

    ConverterGuiProxy cgp(nullptr);
    qmlRegisterUncreatableType<ConverterGuiProxy>("app", 1, 0,
                                                  "ConverterGuiProxy", {});
    engine.rootContext()->setContextProperty(QStringLiteral("converter"), &cgp);
    engine.rootContext()->setContextProperty(QStringLiteral("version"),
                                             VERSION);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return QGuiApplication::exec();
}
