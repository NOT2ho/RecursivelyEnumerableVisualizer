#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);


private:
    void populateScene(QString sf, QString sf2, std::vector<int> dom);
    const int MAX_DOMAIN_RANGE;

    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H