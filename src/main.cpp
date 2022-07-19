#include "CliRunner.hpp"
#include "ConversionModel.hpp"
#include "ConverterGuiProxy.hpp"
#include "version.hpp"

// clang-format off
#ifndef ONLY_CLI
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#else
#include <QtDebug>
#endif
// clang-format on

#include <QCommandLineParser>
#include <QFontDatabase>

auto main(int argc, char **argv) -> int
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef ONLY_CLI
    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("Federico Guerinoni"));
    QCoreApplication::setOrganizationDomain(
        QStringLiteral("Federico Guerinoni"));
    QCoreApplication::setApplicationName(QStringLiteral("qTsConverter"));
    QCoreApplication::setApplicationVersion(swVersion());
#else
#    ifdef Q_OS_WIN
    QQuickWindow::setTextRenderType(
        QQuickWindow::TextRenderType::NativeTextRendering);
#    endif

    QApplication app(argc, argv);
    QApplication::setOrganizationName(QStringLiteral("Federico Guerinoni"));
    QApplication::setOrganizationDomain(QStringLiteral("Federico Guerinoni"));
    QApplication::setApplicationName(QStringLiteral("qTsConverter"));
    QApplication::setWindowIcon(QIcon(":/assets/logos/profile.png"));
    QApplication::setApplicationVersion(swVersion());
#endif

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.setApplicationDescription(swDescription());
    parser.addVersionOption();

    parser.addPositionalArgument("in", "input file.", "[in...]");
    parser.addPositionalArgument("out", "output file.", "[out...]");
    QCommandLineOption noVersion(
        "no-version", "do not print version information into output file");
    parser.addOption(noVersion);
    QCommandLineOption noLocation(
        "no-location", "do not print location information into output file");
    parser.addOption(noLocation);

    parser.process(app);

    auto args = parser.positionalArguments();
    if (!args.isEmpty()) {
        CliRunner cli(std::move(args), parser.isSet(noVersion),
                      parser.isSet(noLocation));
        return cli.run();
#ifdef ONLY_CLI
    } else {
        qWarning() << "no args provided (this is CLI version)";
        return 1;
#endif
    }

#ifndef ONLY_CLI
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
#endif
}
