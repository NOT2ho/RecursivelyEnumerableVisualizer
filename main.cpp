#include <QApplication>
#include "mainwindow.h"
#include <QQmlApplicationEngine>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    MainWindow window;
    window.show();

    return QCoreApplication::exec();
}

