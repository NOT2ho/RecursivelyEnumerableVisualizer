#include "savablewidget.h"

SavableWidget::SavableWidget(QWidget *parent, int dimension)
    : QWidget{parent}, DIM(dimension), savable(false)
{}

bool SavableWidget::saveImage() {
    return false;
}