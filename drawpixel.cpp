#include "drawpixel.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QVarLengthArray>

DrawPixel::DrawPixel(const QColor &color, int x, int y, int val)
    : QGraphicsItem(), RECT (QRectF(0, 0, 10, 10))
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->val = val;
    setZValue((x + y) % 2);;

    setAcceptHoverEvents(true);
}

QRectF DrawPixel::boundingRect() const {
    return RECT;
}

void DrawPixel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    painter->fillRect(RECT, color);
    QColor textColor = QColor(QColorConstants::Black);

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    if (color.lightness() < 200) textColor = QColor(QColorConstants::White);
    // Draw text
    if (lod >= 2.5) {
        QFont font("Ubuntu Mono", 1);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setPen(textColor);
        painter->setFont(font);
        painter->save();
        painter->scale(1, 1);
        painter->drawText(RECT, Qt::AlignCenter, QString("〈%1, %2〉 ↦ %3").arg(x).arg(y).arg(val));
        painter->restore();
    }
}
