#include "linetextframe.h"
#include "drawpixel.h"
#include "visualize2d.h"
#include "savablewidget.h"
#include "view.h"
#include "valuearray2d.h"
#include <QHBoxLayout>
#include <QSplitter>
#include<QDebug>
#include <QJSEngine>
#include <QLineEdit>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include<QMenuBar>
#include<qfiledialog.h>
#include <QtLogging>

Visualize2D::Visualize2D(QWidget *parent, int dimension)
    : SavableWidget(parent), image(new QImage()), scene(new QGraphicsScene(this)),  MAX_DOMAIN_RANGE (500)

{


    View *view = new View();
    view->graphicsView->setScene(scene);

    QFont font ("Ubuntu Mono");
    font.setStyleHint(QFont::Monospace);


    QFont labelFont ("");
    labelFont.setBold(true);

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
    textInputLabel->setFont(labelFont);
    textInputLabel->setText("pixel function");
    textInputLabel->setAlignment(Qt::AlignCenter);

    QLabel *textInputDesc = new QLabel(this);
    textInputDesc->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);
    textInputDesc->setText("\"main\": N × N -> N 함수를 만드세요.");
    textInputDesc->setWordWrap(true);
    textInputLabel->setAlignment(Qt::AlignLeft);

    QLabel *textInput2Label = new QLabel(this);
    textInput2Label->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);
    textInput2Label->setFont(labelFont);
    textInput2Label->setText("color function");
    textInput2Label->setAlignment(Qt::AlignCenter);


    QLabel *textInput2Desc = new QLabel(this);
    textInput2Desc->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);
    textInput2Desc->setText("\"main\": N -> N 함수를 만드세요.");
    textInput2Desc->setWordWrap(true);
    textInput2Label->setAlignment(Qt::AlignLeft);

    LineTextFrame *lineEditx1 = new LineTextFrame(this);
    LineTextFrame *lineEditx2 = new LineTextFrame(this);
    LineTextFrame *lineEdity1 = new LineTextFrame(this);
    LineTextFrame *lineEdity2 = new LineTextFrame(this);

    textInput->setPlainText("main: (x, y) => { \n\tfunction calc(x, y) { \n\t\treturn x + y \n\t} \n return calc(x, y) \n}");
    textInput2->setPlainText("main: (i) => {\n\tfunction color(i) {\n\t\tlet c = i % 256\n\t\treturn colorHelper(c, c, c)\n\t}\n\tfunction colorHelper(r, g, b) {\n\t\treturn b + g * 0x100 + r* 0x10000\n\t}\n\treturn color(i)\n}");



    QPushButton *button = new QPushButton("&Enter", this);
    connect(button, &QPushButton::clicked, this,  [this, textInput, textInput2, lineEditx1, lineEditx2, lineEdity1, lineEdity2, view] () {
        bool *ok = new bool();
        bool *ok2 = new bool();
        bool *ok3 = new bool();
        bool *ok4 = new bool();
        int x1 = lineEditx1->lineEdit->text().toInt(ok);
        int x2 = lineEditx2->lineEdit->text().toInt(ok2);
        int y1 = lineEdity1->lineEdit->text().toInt(ok3);
        int y2 = lineEdity2->lineEdit->text().toInt(ok4);
        auto isInRange = [this](int x) { return x >= 0 && x < MAX_DOMAIN_RANGE; };
        if (x1 >= 0 && y1 >= 0 && isInRange(x2 - x1) && isInRange(y2 - y1) && *ok && *ok2 && *ok3 && *ok4) {
            view->changeName(tr("%1 ≤ x < %2, %3 ≤ y < %4").arg(x1).arg(x2).arg(y1).arg(y2));
            populateScene (
            textInput->toPlainText(),
            textInput2->toPlainText(),
            { x1, x2, y1, y2 }, this->scene);
            savable = true;
            }
        else {
            savable = false;
                QMessageBox msgBox(this);
                msgBox.setText(tr("범위는 %1보다 작은 자연수여야 합니다. 자연수는 0부터 시작합니다. 너무 큰 수를 넣으면 어떻게 될지는 모릅니다.").arg(MAX_DOMAIN_RANGE));
                msgBox.exec();
            }
    });

    button->setFixedSize(QSize(100, 30));

    QVBoxLayout *textInputlayout = new QVBoxLayout();
    textInputlayout->addWidget(textInputLabel, 0);
    textInputlayout->addWidget(textInputDesc, 0);
    textInputlayout->addWidget(textInput, 1);


    QVBoxLayout *textInput2layout = new QVBoxLayout();
    textInput2layout->addWidget(textInput2Label, 0);
    textInput2layout->addWidget(textInput2Desc, 0);
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


    setWindowTitle(tr("recursively enumerable visualizer 2D"));
}

bool Visualize2D::saveImage () {
    if (savable) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "\\",
                                                    tr("Images (*.bmp, *.png, *.jpg)"));
    return image->save(fileName, 0, 100);
    }
    else {
    QMessageBox msgBox(this);
    msgBox.setText(tr("?"));
    msgBox.exec();
    return false;
    }
}

void Visualize2D::populateScene(QString sf, QString sf2, std::vector<int> dom, QGraphicsScene *scene)
{
    scene->clear();
    width = dom[1]-dom[0];
    height = dom[3]-dom[2];
    scene->setSceneRect(0, 0, width *10, height *10);
    valueArray2D valarr = valueArray2D(sf, sf2, dom);
    QJSEngine engine;
    QJSValueList lst;
    image = new QImage(width, height, QImage::Format::Format_ARGB32);
    image->fill(0x00000000);
    int xx = dom[0];
    for (int i = dom[0]*10; i < dom[1]*10; i += 10) {
        int yy = dom[2];
        for (int j = dom[2]*10; j < dom[3]*10; j += 10) {
            auto val = valarr.getValue(xx,yy);
            QColor color(valarr.getColor(val));
            DrawPixel *item = new DrawPixel(color, xx, yy, val);
            item->setPos(QPointF(i, j));
            scene->addItem(item);
            image->setPixelColor(QPoint(xx - dom[0], yy - dom[2]), color);
            yy++;
        }
        xx++;
    }
}