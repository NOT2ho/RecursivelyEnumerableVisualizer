#ifndef LINETEXTFRAME_H
#define LINETEXTFRAME_H

#include <QLabel>
#include <qboxlayout.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
class LineTextFrame;


class LineTextFrame : public QHBoxLayout {
    Q_OBJECT
public:
    explicit LineTextFrame(QWidget *parent = nullptr);
    void toGroupBox(QString defval, QString name);
    QLineEdit *lineEdit;
    QGroupBox *groupBox;


private:
    QLabel *label;
    QHBoxLayout *lineTextLayout;

signals:
};


#endif // LINETEXTFRAME_H
