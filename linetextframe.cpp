#include "linetextframe.h"
#include<QValidator>

LineTextFrame::LineTextFrame(QWidget *parent)
    : QHBoxLayout () {

    lineEdit = new QLineEdit(parent);
    label = new QLabel(parent);
    lineTextLayout = new QHBoxLayout();
    groupBox = new QGroupBox(parent);


}

void LineTextFrame::toGroupBox(QString defval, QString name) {
    lineEdit->setText(defval);
    label->setText(name);
    lineEdit->setFixedSize(QSize(100, 30));
    lineTextLayout->addWidget(label, 0, Qt::AlignCenter);
    lineTextLayout->addWidget(lineEdit, 0, Qt::AlignCenter);
    groupBox->setLayout(lineTextLayout);
    groupBox->setFixedSize(QSize(120, 50));
    groupBox->setStyleSheet( "border: none");


}
