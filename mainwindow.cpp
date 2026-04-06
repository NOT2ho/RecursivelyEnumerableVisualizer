#include "linetextframe.h"
#include "drawpixel.h"
#include "mainwindow.h"
#include "view.h"
#include "valuearray2d.h"
#include <QHBoxLayout>
#include <QSplitter>
#include<QDebug>
#include <QJSEngine>
#include <QLineEdit>
#include <qgroupbox.h>
#include <qlabel.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), scene(new QGraphicsScene(this)), MAX_DOMAIN_RANGE (500)

{
    View *view = new View();
    view->graphicsView->setScene(scene);

    QFont font ("Ubuntu Mono");
    font.setStyleHint(QFont::Monospace);

    QTextEdit *textInput = new QTextEdit("", this);
    textInput->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    textInput->setStyleSheet("border: none; background-color: #fefefe; border-radius: 5px;");
    textInput->setFont(font);
    textInput->setTabStopDistance(QFontMetrics(font).averageCharWidth()*4);

    QTextEdit *textInput2 = new QTextEdit("", this);
    textInput2->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    textInput2->setStyleSheet("border: none; background-color: #fefefe; border-radius: 5px;");
    textInput2->setFont(font);
    textInput2->setTabStopDistance(QFontMetrics(font).averageCharWidth()*4);

    QLabel *textInputLabel = new QLabel(this);
    textInputLabel->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);
    textInputLabel->setText("pixel function");
    textInputLabel->setAlignment(Qt::AlignCenter);

    QLabel *textInput2Label = new QLabel(this);
    textInput2Label->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);
    textInput2Label->setText("color function");
    textInput2Label->setAlignment(Qt::AlignCenter);


    LineTextFrame *lineEditx1 = new LineTextFrame(this);
    LineTextFrame *lineEditx2 = new LineTextFrame(this);
    LineTextFrame *lineEdity1 = new LineTextFrame(this);
    LineTextFrame *lineEdity2 = new LineTextFrame(this);

    textInput->setPlainText("main: (x, y) => { \n\tfunction calc(x, y) { \n\t\treturn x + y \n\t} \n return calc(x, y) \n}");
    textInput2->setPlainText("main: (i) => {\n\tfunction color(i) {\n\t\tlet c = i % 256\n\t\treturn colorHelper(c, c, c)\n\t}\n\tfunction colorHelper(r, g, b) {\n\t\treturn b + g * 0x100 + r* 0x10000\n\t}\n\treturn color(i)\n}");

    QPushButton *button = new QPushButton("&Enter", this);
    connect(button, &QPushButton::clicked, this,  [this, textInput, textInput2, lineEditx1, lineEditx2, lineEdity1, lineEdity2, view] () {
        int x1 =  lineEditx1->lineEdit->text().toInt();
        int x2 = lineEditx2->lineEdit->text().toInt();
        int y1 = lineEdity1->lineEdit->text().toInt();
        int y2 = lineEdity2->lineEdit->text().toInt();
        auto isInRange = [this](int x) { return x >= 0 && x < MAX_DOMAIN_RANGE; };
        if (x1 >= 0 && y1 >= 0 && isInRange(x2 - x1) && isInRange(y2 - y1)) {
            view->changeName(tr("%1 ≤ x < %2, %3 ≤ y < %4").arg(x1).arg(x2).arg(y1).arg(y2));
            populateScene (
            textInput->toPlainText(),
            textInput2->toPlainText(),
            { x1, x2, y1, y2 });
            }
        else qInfo("wow");
    });

    button->setFixedSize(QSize(100, 30));


    QVBoxLayout *textInputlayout = new QVBoxLayout();
    textInputlayout->addWidget(textInputLabel, 0);
    textInputlayout->addWidget(textInput, 1);

    QVBoxLayout *textInput2layout = new QVBoxLayout();
    textInput2layout->addWidget(textInput2Label, 0);
    textInput2layout->addWidget(textInput2, 1);

    QGroupBox *textInputBox = new QGroupBox(this);
    QGroupBox *textInput2Box = new QGroupBox(this);

    textInputBox->setLayout(textInputlayout);
    textInput2Box->setLayout(textInput2layout);

    QSplitter *splitter = new QSplitter();
    splitter->setChildrenCollapsible(false);
    splitter->addWidget(view);
    splitter->addWidget(textInputBox);
    splitter->addWidget(textInput2Box);
    splitter->setStretchFactor(0,2);
    splitter->setStretchFactor(1,1);
    splitter->setStretchFactor(2,1);

    lineEditx1->toGroupBox("0", "x >=");
    lineEditx2->toGroupBox("100", "x <");
    lineEdity1->toGroupBox("0", "y >=");
    lineEdity2->toGroupBox("100", "y <");

    QHBoxLayout *domainLayout = new QHBoxLayout();
    domainLayout->addWidget(lineEditx1->groupBox);
    domainLayout->addWidget(lineEditx2->groupBox);
    domainLayout->addWidget(lineEdity1->groupBox);
    domainLayout->addWidget(lineEdity2->groupBox);
    domainLayout->setSpacing(10);


    QGridLayout *layout = new QGridLayout();
    layout->addWidget(splitter, 1, 0);
    layout->addLayout(domainLayout,2,0);
    layout->addWidget(button,3,0, Qt::AlignHCenter);
    setLayout(layout);


    setWindowTitle(tr("recursive image generator"));
}



void MainWindow::populateScene(QString sf, QString sf2, std::vector<int> dom)
{
    scene->clear();
    scene->setSceneRect(0, 0, ( dom[1]-dom[0]) *10, ( dom[3]-dom[2]) *10);
    valueArray2D valarr = valueArray2D(sf, sf2, dom);
    QJSEngine engine;
    QJSValueList lst;

    int xx = 0;
    for (int i = dom[0]*10; i < dom[1]*10; i += 10) {
        int yy = 0;
        for (int j = dom[2]*10; j < dom[3]*10; j += 10) {
            QColor color(valarr.getColor(valarr.getValue(xx,yy)));
            DrawPixel *item = new DrawPixel(color, xx, yy, valarr.getValue(xx,yy));
            item->setPos(QPointF(i, j));
            scene->addItem(item);
            yy++;
        }
        xx++;
    }


}