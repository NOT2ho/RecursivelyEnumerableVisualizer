#include "drawpixel.h"
#include "linetextframe.h"
#include "visualize3d.h"
#include "valuearray3d.h"
#include "visualize2d.h"
#include "view.h"
#include <QHBoxLayout>
#include <QSplitter>
#include<QDebug>
#include <QJSEngine>
#include <QLineEdit>
#include <qgroupbox.h>
#include <qjsonobject.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include<QMenuBar>
#include <qslider.h>
#include <algorithm>
#include <QtLogging>
#include <qstyle.h>
#include <qtimer.h>
#include<qfiledialog.h>
#include <qtoolbutton.h>

Visualize3D::Visualize3D(QWidget *parent, int dimension, int xstart, int xend, int ystart, int yend, int tstart, int tend, QByteArray pixel_function, QByteArray color_function)
    : SavableWidget(parent), tLabel(new QLabel(this)), timeSlider(new QSlider(Qt::Orientation::Horizontal, this)), view(new View()), MAX_DOMAIN_RANGE (500)

{
    this->xstart = xstart;
    this->xend = xend;
    this->ystart = ystart;
    this->yend = yend;
    this->tstart = tstart;
    this->tend = tend;
    this->pixel_function = pixel_function;
    this->color_function = color_function;

    imageSequence= {};
    makeFrames(this->pixel_function, this->color_function, {this->xstart, this->xend, this->ystart, this->yend, this->tstart, this->tend});


    QFont font ("Ubuntu Mono");
    font.setStyleHint(QFont::Monospace);

    tLabel->setText("t= ");

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
    textInputDesc->setText("\"main\": N × N × N -> N 함수를 만드세요.");
    textInputDesc->setWordWrap(true);
    textInputDesc->setAlignment(Qt::AlignLeft);

    QLabel *textInput2Label = new QLabel(this);
    textInput2Label->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);
    textInput2Label->setFont(labelFont);
    textInput2Label->setText("color function");
    textInput2Label->setAlignment(Qt::AlignCenter);


    QLabel *textInput2Desc = new QLabel(this);
    textInput2Desc->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);
    textInput2Desc->setText("\"main\": N -> N 함수를 만드세요.");
    textInput2Desc->setWordWrap(true);
    textInput2Desc->setAlignment(Qt::AlignLeft);

    LineTextFrame *lineEditx1 = new LineTextFrame(this);
    LineTextFrame *lineEditx2 = new LineTextFrame(this);
    LineTextFrame *lineEdity1 = new LineTextFrame(this);
    LineTextFrame *lineEdity2 = new LineTextFrame(this);
    LineTextFrame *lineEditz1 = new LineTextFrame(this);
    LineTextFrame *lineEditz2 = new LineTextFrame(this);


    textInput->setPlainText(this->pixel_function);
    textInput2->setPlainText(this->color_function);


    QPushButton *button = new QPushButton("&Enter", this);
    connect(button, &QPushButton::clicked, this,  [this, textInput, textInput2, lineEditx1, lineEditx2, lineEdity1, lineEdity2, lineEditz1, lineEditz2] () {
        std::vector<bool *> ok{ new bool(), new bool(), new bool(), new bool(), new bool(), new bool()};
        int x1 = lineEditx1->lineEdit->text().toInt(ok[0]);
        int x2 = lineEditx2->lineEdit->text().toInt(ok[1]);
        int y1 = lineEdity1->lineEdit->text().toInt(ok[2]);
        int y2 = lineEdity2->lineEdit->text().toInt(ok[3]);
        int z1 = lineEditz1->lineEdit->text().toInt(ok[4]);
        int z2 = lineEditz2->lineEdit->text().toInt(ok[5]);
        bool allOk = std::all_of(ok.begin(), ok.end(), [](bool *x){return *x;});
        auto isInRange = [this](int x) { return x >= 0 && x < MAX_DOMAIN_RANGE; };
        if (x1 >= 0 && y1 >= 0 && z1 >= 0 && isInRange(x2 - x1) && isInRange(y2 - y1) && isInRange(z2 - z1) && allOk) {
            imageSequence= {};
            this->view->changeName(tr("%1 ≤ x < %2, %3 ≤ y < %4, %5 ≤ t < %6").arg(x1).arg(x2).arg(y1).arg(y2).arg(z1).arg(z2));
            this->xstart = x1;
            this->xend = x2;
            this->ystart = y1;
            this->yend = y2;
            this->tstart = z1;
            this->tend = z2;
            this->pixel_function = textInput->toPlainText().toUtf8();
            this->color_function = textInput2->toPlainText().toUtf8();
            makeFrames(
            textInput->toPlainText(),
            textInput2->toPlainText(),
            { x1, x2, y1, y2, z1, z2});
            setWindowTitle(tr("%1 ≤ x < %2, %3 ≤ y < %4, %5 ≤ y < %6").arg(x1).arg(x2).arg(y1).arg(y2).arg(z1).arg(z2));
            tLabel->setText(tr("t= %1").arg(timeSlider->minimum()));
            currentImage = imageSequence[timeSlider->minimum()];
            savable = true;
        }
        else {
                QMessageBox msgBox(this);
                msgBox.setText(tr("범위는 %1보다 작은 자연수여야 합니다. 자연수는 0부터 시작합니다. 너무 큰 수를 넣으면 어떻게 될지는 모릅니다.").arg(MAX_DOMAIN_RANGE));
                msgBox.exec();
                savable = false;
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

    LineTextFrame *lineEditSetTimer = new LineTextFrame(this);
    lineEditSetTimer->toGroupBox("15", "fps");

    QToolButton *playButton = new QToolButton(this);
    playButton->setText("▶");
    connect(playButton, &QToolButton::clicked, this, [lineEditSetTimer, this] () {
        bool *ok = new bool(false);
        float fps = lineEditSetTimer->lineEdit->text().toFloat(ok);
        int min = timeSlider->minimum();
        int max = timeSlider->maximum();
        if (*ok && fps > 0) {

                QTimer *timer = new QTimer(this);
                timer->setInterval(1/fps);
                timer->start();
                connect(timer, &QTimer::timeout, timer, [this, min, max, timer](){
                    auto val = timeSlider->value();
                    if (val < max) timeSlider->setValue(val+1);

                    else {  timeSlider->setValue(min);
                            timer->stop();
                        }
                });

        }
        else { QMessageBox msgBox(this);
             msgBox.setText(tr("0보다 큰 실수를 넣으세요."));
             msgBox.exec();
        }
    });
    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    QToolButton *tplusIcon = new QToolButton;
    tplusIcon->setAutoRepeat(true);
    tplusIcon->setAutoRepeatInterval(1);
    tplusIcon->setAutoRepeatDelay(300);
    tplusIcon->setText(tr("+"));
    tplusIcon->setIconSize(iconSize);
    QToolButton *tminusIcon = new QToolButton;
    tminusIcon->setAutoRepeat(true);
    tminusIcon->setAutoRepeatInterval(1);
    tminusIcon->setAutoRepeatDelay(300);
    tminusIcon->setText(tr("-"));
    tminusIcon->setIconSize(iconSize);


    tLabel->setFrameStyle(QFrame::NoFrame | QFrame::NoFrame);

    tLabel->setWordWrap(true);
    tLabel->setAlignment(Qt::AlignLeft);

    QHBoxLayout *timerLayout = new QHBoxLayout(this);
    timerLayout->addWidget(tLabel);
    timerLayout->addWidget(tminusIcon);
    timerLayout->addWidget(timeSlider);
    timerLayout->addWidget(tplusIcon);
    timerLayout->addWidget(lineEditSetTimer->groupBox);
    timerLayout->addWidget(playButton);


    connect(tplusIcon, &QAbstractButton::clicked, this, &::Visualize3D::zplus);
    connect(tminusIcon, &QAbstractButton::clicked, this, &::Visualize3D::zminus);

    QGroupBox *timerLayoutBox = new QGroupBox(this);
    timerLayoutBox->setLayout(timerLayout);

    QVBoxLayout *viewLayout = new QVBoxLayout(this);
    viewLayout->addWidget(view);
    viewLayout->addWidget(timerLayoutBox);

    QGroupBox *viewLayoutBox = new QGroupBox(this);
    viewLayoutBox->setLayout(viewLayout);

    QSplitter *splitter = new QSplitter();
    splitter->setChildrenCollapsible(false);
    splitter->addWidget(viewLayoutBox);
    splitter->addWidget(textInputBox);
    splitter->addWidget(textInput2Box);
    splitter->setStretchFactor(0,2);
    splitter->setStretchFactor(1,1);
    splitter->setStretchFactor(2,1);

    lineEditx1->toGroupBox(QString::number(this->xstart), "x >=");
    lineEditx2->toGroupBox(QString::number(this->xend), "x <");
    lineEdity1->toGroupBox(QString::number(this->ystart), "y >=");
    lineEdity2->toGroupBox(QString::number(this->yend), "y <");
    lineEditz1->toGroupBox(QString::number(this->tstart), "z >=");
    lineEditz2->toGroupBox(QString::number(this->tend), "z <");

    QHBoxLayout *domainLayout = new QHBoxLayout();
    domainLayout->addWidget(lineEditx1->groupBox);
    domainLayout->addWidget(lineEditx2->groupBox);
    domainLayout->addWidget(lineEdity1->groupBox);
    domainLayout->addWidget(lineEdity2->groupBox);
    domainLayout->addWidget(lineEditz1->groupBox);
    domainLayout->addWidget(lineEditz2->groupBox);
    domainLayout->setSpacing(10);


    QGridLayout *layout = new QGridLayout();
    layout->addWidget(splitter, 1, 0);
    layout->addLayout(domainLayout,2,0);
    layout->addWidget(button, 3,0, Qt::AlignHCenter);
    setLayout(layout);



}

void Visualize3D::zplus()
{
    timeSlider->setValue(timeSlider->value() + 1);
}

void Visualize3D::zminus()
{
    timeSlider->setValue(timeSlider->value() - 1);
}



bool Visualize3D::saveImage () {
    if (savable) {
        QFileDialog *dialog = new QFileDialog();
        dialog->setDefaultSuffix("png");
        QString fileName = dialog->getSaveFileName(this, tr("Save File"),
                                                   "\\",
                                                   tr("Image Files (*.png *.jpg *.bmp)"));
        return currentImage->save(fileName, 0, 100);
    }
    else {
        QMessageBox msgBox(this);
        msgBox.setText(tr("?"));
        msgBox.exec();
        return false;
    }
}


bool Visualize3D::saveProject () {

    QJsonObject functionObject
        {
            {"pixel-function", QJsonValue::fromVariant(pixel_function)},
            {"color-function", QJsonValue::fromVariant(color_function)}
        };

    QJsonObject domainObject
        {
            {"x1", xstart},
            {"x2", xend},
            {"y1", ystart},
            {"y2", yend},
            {"t1", tstart},
            {"t2", tend}
        };

    QJsonObject object
        {
            {"dimension", 3},
            {"functions", functionObject},
            {"domains", domainObject}
        };


    if (savable) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "\\",
                                                        tr("JSON (*.json"));


        QFile saveFile(fileName);
        if (!saveFile.open(QIODevice::WriteOnly)) {        qWarning("Couldn't open save file.");
            return false; }
        QByteArray jsonFile = QJsonDocument(object).toJson();
        saveFile.write(jsonFile);
        return true;

    }
    else {
        QMessageBox msgBox(this);
        msgBox.setText(tr("?"));
        msgBox.exec();
        return false;
    }

}





bool Visualize3D::saveImages () {

    if (savable) {
        QFileDialog *dialog = new QFileDialog();
        dialog->setDefaultSuffix("png");
        QString fileName = dialog->getSaveFileName(this, tr("Save File"),
                                                   "\\",
                                                   tr("Image Files (*.png *.jpg *.bmp)"));

        QString basename = QFileInfo(fileName).baseName();
        QString extension = QFileInfo(fileName).suffix();
        QString path = QFileInfo(fileName).path();
        bool saved = true;
        int i = 0;
        for (QImage *frame : imageSequence ) {
            QString frameName = QDir::cleanPath(path + QDir::separator() + basename + "_" + QString::number(i) + "." + extension);
            saved = saved && frame->save(frameName, 0, 100);
            i++;
        }
        return saved;
    }
    else {
        QMessageBox msgBox(this);
        msgBox.setText(tr("?"));
        msgBox.exec();
        return false;
    }
}


void Visualize3D::populateScene(QString sf, QString sf2, std::vector<int> dom, int z, QGraphicsScene *scene)
{
    scene->clear();
    width = dom[1]-dom[0];
    height = dom[3]-dom[2];
    scene->setSceneRect(0, 0, width *10, height *10);
    QImage *image = new QImage(width, height, QImage::Format::Format_ARGB32);
    image->fill(0x00000000);
    valueArray3D valarr = valueArray3D(sf, sf2);
    QJSEngine engine;
    QJSValueList lst;

    int xx = dom[0];
    for (int i = dom[0]*10; i < dom[1]*10; i += 10) {
        int yy = dom[2];
        for (int j = dom[2]*10; j < dom[3]*10; j += 10) {
            auto val = valarr.getValue(xx,yy,z);
            QColor color(valarr.getColor(val));
            DrawPixel *item = new DrawPixel(color, xx, yy, z, val);
            item->setPos(QPointF(i, j));
            scene->addItem(item);
            image->setPixelColor(QPoint(xx - dom[0], yy - dom[2]), color);
            yy++;
        }
        xx++;
    }
    imageSequence.push_back(new QImage(*image));
}





void Visualize3D::makeFrames(QString sf, QString sf2, std::vector<int> dom) {
    int z1 = dom[4];
    int z2 = dom[5];
    std::vector<int> subdom = {dom.begin(), dom.end() -2};
    for (int i = z1 ; i < z2 ; i++) {
        QGraphicsScene *scene = new QGraphicsScene(this);
        populateScene(sf, sf2, subdom, i, scene);
        scenes.push_back(scene);
    }

    timeSlider->setMinimum(z1);
    timeSlider->setMaximum(z2-1);
    timeSlider->setValue(z1);
    timeSlider->setTickPosition(QSlider::TicksBelow);
    connect(timeSlider, &QAbstractSlider::valueChanged, this, [this]() {
            this->view->graphicsView->setScene(scenes[timeSlider->value() - timeSlider->minimum()]);
            this->currentImage = imageSequence[timeSlider->value() - timeSlider->minimum()];
            this->tLabel->setText(tr("t= %1").arg(timeSlider->value()));
    });
    this->view->graphicsView->setScene(scenes[timeSlider->value() - timeSlider->minimum()]);
}