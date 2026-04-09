#ifndef VISUALIZE3D_H
#define VISUALIZE3D_H

#include "savablewidget.h"
#include "view.h"
#include <QWidget>
#include <QPushButton>
#include <qlabel.h>
#include <qslider.h>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class Visualize3D : public SavableWidget
{
    Q_OBJECT
public:
    Visualize3D(QWidget *parent = nullptr, int dimension = 3, int xstart = 0, int xend = 100, int ystart = 0, int yend = 100, int tstart = 0, int tend = 30, QByteArray pixel_function = "main: (x, y, z) => { \n\tfunction calc(x, y, z) { \n\t\treturn x + y + z\n\t} \n return calc(x, y, z) \n}", QByteArray color_function = "main: (i) => {\n\tfunction color(i) {\n\t\tlet c = i % 256\n\t\treturn colorHelper(c, c, c)\n\t}\n\tfunction colorHelper(r, g, b) {\n\t\treturn b + g * 0x100 + r* 0x10000\n\t}\n\treturn color(i)\n}");
    bool saveImage () override;
    bool saveImages () override;
    bool saveProject () override;
    QImage *image;
private:
    void makeFrames(QString sf, QString sf2, std::vector<int> dom);
    void populateScene(QString sf, QString sf2, std::vector<int> dom, int z, QGraphicsScene *scene);
    const int MAX_DOMAIN_RANGE;
    View *view;
    QWidget *visualize3d;
    QSlider *timeSlider;
    std::vector<QGraphicsScene *> scenes;
    std::vector<QImage *> imageSequence;
    int width;
    int height;
    QLabel *tLabel;
    void zplus();
    void zminus();
    int xstart;
    int ystart;
    int tstart;
    int xend;
    int yend;
    int tend;
    QByteArray pixel_function;
    QByteArray color_function;

};

#endif // VISUALIZE3D_H
