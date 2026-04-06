#ifndef VISUALIZE3D_H
#define VISUALIZE3D_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class Visualize3D : public QWidget
{
    Q_OBJECT
public:
    Visualize3D(QWidget *parent = nullptr);


private:
    void populateScene(QString sf, QString sf2, std::vector<int> dom);
    const int MAX_DOMAIN_RANGE;


    QGraphicsScene *scene;
};

#endif // VISUALIZE3D_H
