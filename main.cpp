#include "mainwindow.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    MainWindow mainWindow;
    mainWindow.show();

    return QCoreApplication::exec();
}

