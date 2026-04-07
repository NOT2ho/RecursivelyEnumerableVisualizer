#ifndef SAVABLEWIDGET_H
#define SAVABLEWIDGET_H

#include <QWidget>



class SavableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SavableWidget(QWidget *parent = nullptr, int dimension = -1);
    bool savable;
    const int DIM;
    virtual bool saveImage() ;


signals:
};


#endif // SAVABLEWIDGET_H
