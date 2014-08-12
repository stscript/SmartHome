#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "httpControl.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<HttpControl>("HttpControl", 1, 0, "HttpCTL");
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
