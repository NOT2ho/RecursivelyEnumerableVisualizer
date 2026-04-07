#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "savablewidget.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void seeHelp();
    void seeSeemore();
    void saveasimage();
    void showMsgBox(QString title, QString text);
    void saveasimagesequence() ;
    QTabWidget *tabWidget;
signals:

};

#endif // MAINWINDOW_H
