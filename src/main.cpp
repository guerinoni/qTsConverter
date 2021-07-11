#include "CliRunner.hpp"
#include "ConversionModel.hpp"
#include "ConverterGuiProxy.hpp"
#include "version.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QFontDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

auto main(int argc, char **argv) -> int
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef Q_OS_WIN
    QQuickWindow::setTextRenderType(
        QQuickWindow::TextRenderType::NativeTextRendering);
#endif

    QApplication app(argc, argv);
    QApplication::setOrganizationName(QStringLiteral("Federico Guerinoni"));
    QApplication::setOrganizationDomain(QStringLiteral("Federico Guerinoni"));
    QApplication::setApplicationName(QStringLiteral("qTsConverter"));
    QApplication::setWindowIcon(QIcon(":/assets/logos/profile.png"));
    QApplication::setApplicationVersion(swVersion());

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.setApplicationDescription(swDescription());
    parser.addVersionOption();

    parser.addPositionalArgument("in", "input file.", "[in...]");
    parser.addPositionalArgument("out", "output file.", "[out...]");

    parser.process(app);

    auto args = parser.positionalArguments();
    if (!args.isEmpty()) {
        CliRunner cli(std::move(args));
        return cli.run();
    }

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
