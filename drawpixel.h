#ifndef DRAWPIXEL_H
#define DRAWPIXEL_H

#include <QColor>
#include <QGraphicsItem>

class DrawPixel : public QGraphicsItem
{
public:
    DrawPixel(const QColor &color, int x, int y, int val);
    DrawPixel(const QColor &color, int x, int y, int z, int val);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    int x;
    int y;
    int *z = nullptr;
    int val;
    QColor color;
    const QRectF RECT;
};


#endif // DRAWPIXEL_H
