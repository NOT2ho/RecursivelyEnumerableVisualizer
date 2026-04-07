#ifndef VISUALIZE2D_H
#define VISUALIZE2D_H

#include "savablewidget.h"
#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class Visualize2D : public SavableWidget
{
    Q_OBJECT
public:
    Visualize2D(QWidget *parent = nullptr, int dimension = 2);
    void populateScene(QString sf, QString sf2, std::vector<int> dom, QGraphicsScene *scene);
    bool saveImage () override;
private:

    const int MAX_DOMAIN_RANGE;
    int width;
    int height;
    QImage *image;

    QGraphicsScene *scene;
};

#endif // VISUALIZE2D_H
