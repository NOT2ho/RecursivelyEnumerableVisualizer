#ifndef VISUALIZE3D_H
#define VISUALIZE3D_H

#include "savablewidget.h"
#include "view.h"
#include <QWidget>
#include <QPushButton>
#include <qslider.h>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class Visualize3D : public SavableWidget
{
    Q_OBJECT
public:
    Visualize3D(QWidget *parent = nullptr, int dimension = 3);
    bool saveImage () override;

private:
    std::vector<QGraphicsScene *> makeFrames(QString sf, QString sf2, std::vector<int> dom);
    void populateScene(QString sf, QString sf2, std::vector<int> dom, int z, QGraphicsScene *scene);
    const int MAX_DOMAIN_RANGE;
    View *view;
    QWidget *visualize3d;
    QSlider *timeSlider;
    QImage *currentImage;
    std::vector<QImage *> imageSequence;
    int width;
    int height;
    int tRange;
};

#endif // VISUALIZE3D_H
