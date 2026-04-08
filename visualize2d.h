#ifndef VISUALIZE2D_H
#define VISUALIZE2D_H

#include "savablewidget.h"
#include <QWidget>
#include <QPushButton>
#include<QByteArray>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class Visualize2D : public SavableWidget
{
    Q_OBJECT
public:
    Visualize2D(QWidget *parent = nullptr, int dimension = 2, int xstart = 0, int xend = 100, int ystart = 0, int yend = 100, QByteArray pixel_function = "main: (x, y) => { \n\tfunction calc(x, y) { \n\t\treturn x + y \n\t} \n return calc(x, y) \n}", QByteArray color_function = "main: (i) => {\n\tfunction color(i) {\n\t\tlet c = i % 256\n\t\treturn colorHelper(c, c, c)\n\t}\n\tfunction colorHelper(r, g, b) {\n\t\treturn b + g * 0x100 + r* 0x10000\n\t}\n\treturn color(i)\n}");
    void populateScene(QString sf, QString sf2, std::vector<int> dom, QGraphicsScene *scene);
    bool saveImage () override;
private:

    const int MAX_DOMAIN_RANGE;
    QByteArray pixel_function;
    QByteArray color_function;
    int xstart;
    int xend;
    int ystart;
    int yend;
    int width;
    int height;
    QImage *image;
    bool saveProject () override;

    QGraphicsScene *scene;
};

#endif // VISUALIZE2D_H
