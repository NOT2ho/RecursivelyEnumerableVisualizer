#ifndef VISUALIZE2D_H
#define VISUALIZE2D_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class Visualize2D : public QWidget
{
    Q_OBJECT
public:
    Visualize2D(QWidget *parent = nullptr);


private:
    void populateScene(QString sf, QString sf2, std::vector<int> dom);
    const int MAX_DOMAIN_RANGE;


    QGraphicsScene *scene;
};

#endif // VISUALIZE2D_H
