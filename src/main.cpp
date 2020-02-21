#include "ConverterGuiProxy.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Federico Guerinoni");
    app.setOrganizationDomain("Federico Guerinoni");

    QQmlApplicationEngine engine;

    ConverterGuiProxy cgp;
    engine.rootContext()->setContextProperty(QStringLiteral("converter"), &cgp);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return QGuiApplication::exec();
}
