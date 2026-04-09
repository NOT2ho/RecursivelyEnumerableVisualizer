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
    void saveasimage();
    void showMsgBox(QString title, QString text);
    void saveasimagesequence() ;
    void saveproject() ;
    void openProject();
    void seeWhylower();

    QIcon findIcon();
    QTabWidget *tabWidget;
signals:

};

#endif // MAINWINDOW_H
