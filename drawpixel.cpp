#include "drawpixel.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QVarLengthArray>
#include <sstream>

DrawPixel::DrawPixel(const QColor &color, int x, int y, int val)
    : QGraphicsItem(), RECT (QRectF(0, 0, 10, 10))
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->val = val;

    setAcceptHoverEvents(true);
}

DrawPixel::DrawPixel(const QColor &color, int x, int y, int z, int val)
    : QGraphicsItem(), RECT (QRectF(0, 0, 10, 10))
{
    this->x = x;
    this->y = y;
    this->z = new int(z);
    this->color = color;
    this->val = val;

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
    if (lod >= 2.5) {
        QFont font("Malgun Gothic", 1);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setPen(textColor);
        painter->setFont(font);
        painter->save();
        painter->scale(1, 1);
        std::stringstream ss;
        if (z == nullptr)
            ss << "〈" << x << ", " << y << "〉 ↦ " << val;
        else ss << "〈" << x << ", " << y << ", " << *z << "〉 ↦ " << val;
        painter->drawText(RECT, Qt::AlignCenter, QString::fromStdString(ss.str()));
        painter->restore();
    }
}
