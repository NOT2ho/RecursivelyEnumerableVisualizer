#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void seeHelp();
    void seeSeemore();
    void saveasimage(QWidget *widget);
    void showMsgBox(QString title, QString text);
signals:

};

#endif // MAINWINDOW_H
