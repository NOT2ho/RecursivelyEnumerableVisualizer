#include "mainwindow.h"
#include "visualize2D.h"
#include "visualize3D.h"
#include <qdir.h>
#include <qdockwidget.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qtabwidget.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, tabWidget(new QTabWidget(this))
{
    setWindowTitle(tr("r.e. visualizer"));


    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *windowMenu = new QMenu("window", this);
    QMenu *fileMenu = new QMenu("file", this);
    QMenu *helpMenu = new QMenu("help", this);
    QAction *saveasimageAct = new QAction("save image", this);
    QAction *loadprojectAct = new QAction("load project", this);
    QAction *saveasimagesequenceAct = new QAction("save image sequence", this);
    QAction *whynosynthhighlightAct = new QAction("why no syntax highlighter?", this);

    QAction *saveprojectAct = new QAction("save project", this);
    QAction *helpAct = new QAction("help..", this);
    QAction *seemoreAct = new QAction("version", this);
    QAction *whylowerAct = new QAction("why everything is lowercase?", this);
    QAction *add2dtabAct = new QAction("add 2d tab", this);
    QAction *add3dtabAct = new QAction("add 3d tab", this);
    menuBar->addMenu(fileMenu);
    connect(helpAct, &QAction::triggered, this, [this](){this->seeHelp();});
    connect(seemoreAct, &QAction::triggered, this, [this](){this->seeSeemore();});
    connect(whylowerAct, &QAction::triggered, this, [this](){this->seeWhylower();});
    fileMenu->addAction(saveasimageAct);

    fileMenu->addAction(saveasimagesequenceAct);
    fileMenu->addAction(saveprojectAct);
    fileMenu->addSeparator();
    fileMenu->addAction(loadprojectAct);
    helpMenu->addAction(helpAct);
    helpMenu->addAction(seemoreAct);
    helpMenu->addAction(whylowerAct);
    helpMenu->addAction(whynosynthhighlightAct);
    windowMenu->addAction(add2dtabAct);
    windowMenu->addAction(add3dtabAct);

    menuBar->addMenu(windowMenu);
    menuBar->addMenu(helpMenu);
    this->setMenuBar(menuBar);

    Visualize2D *vis2d = new Visualize2D(this);
    Visualize3D *vis3d = new Visualize3D(this);

    tabWidget->setTabsClosable(true);
    tabWidget->addTab(vis2d, tr("2d vis"));
    tabWidget->addTab(vis3d, tr("3d vis"));
    this->setCentralWidget(tabWidget);


    connect(add2dtabAct, &QAction::triggered, this, [this](){
        int count =    tabWidget->count();
            this->tabWidget->addTab(new Visualize2D(this), tr("2d vis"));
            tabWidget->setCurrentWidget(tabWidget->widget(count));});
    connect(add3dtabAct, &QAction::triggered, this, [this](){
        int count =    tabWidget->count();
        this->tabWidget->addTab(new Visualize3D(this), tr("3d vis"));
        tabWidget->setCurrentWidget(tabWidget->widget(count));
    });

    connect(saveasimageAct, &QAction::triggered, this, [this](){saveasimage();});
    connect(saveasimagesequenceAct, &QAction::triggered, this, [this](){saveasimagesequence();});
    connect(saveprojectAct, &QAction::triggered, this, [this](){saveproject();});
    connect(loadprojectAct, &QAction::triggered, this, [this](){openProject();});
    connect(whynosynthhighlightAct, &QAction::triggered, this, [this](){seeWhynosynthhighlight();});
}



void MainWindow::seeHelp() {
    showMsgBox("도움", "JavaScript를 사용하여 함수를 입력하세요. 입출력이 자연수인지, 인자 수가 정확한지를 확인하세요. 하단의 입력창에서 범위를 설정할 수 있습니다.");
}

void MainWindow::seeSeemore() {
    showMsgBox(tr("설명"), "버전: test v0.06091<br></br><a href='https://github.com/NOT2ho/RecursivelyEnumerableVisualizer'>github</a>" );
}

void MainWindow::seeWhylower() {

    showMsgBox("왜 모든 것이 소문자인가요?", "마음에 들지 않으면 pull request 보내십시오.");
}

void MainWindow::seeWhynosynthhighlight() {

    showMsgBox("신택스 하이라이터가 없는 것이 마음에 들지 않나요?", "불만이 있으시면 <a href='https://github.com/NOT2ho/RecursivelyEnumerableVisualizer/pulls'>여기</a>를 누르십시오.");
}

void MainWindow::showMsgBox(QString title, QString text) {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(text);
    msgBox.exec();
}

void MainWindow::openProject () {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "\\",
                                                    tr("JSON (*.json)")
                                                    );
    auto name = QFileInfo(fileName).baseName();
    QFile loadFile(fileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        showMsgBox("파일 저장 실패", "당신 잘못"); }

    else {
        int count =    tabWidget->count();
    QByteArray saveData = loadFile.readAll();
    QJsonObject obj = QJsonDocument::fromJson(saveData).object();
    if (obj.value("dimension") == 2) {
        QJsonObject functions = obj.value("functions").toObject();
        QByteArray pixel_function =functions.value("pixel-function").toString().toUtf8();
        QByteArray color_function =functions.value("color-function").toString().toUtf8();
        QJsonObject domains = obj.value("domains").toObject();
        int x1 = domains.value("x1").toInt();
        int x2 = domains.value("x2").toInt();
        int y1 = domains.value("y1").toInt();
        int y2 = domains.value("y2").toInt();
        this->tabWidget->addTab(new Visualize2D(this, 2, x1, x2, y1, y2, pixel_function, color_function), name);
        tabWidget->setCurrentWidget(tabWidget->widget(count));
    }
    else if (obj.value("dimension") == 3) {
        QJsonObject functions = obj.value("functions").toObject();
        QByteArray pixel_function =functions.value("pixel-function").toString().toUtf8();
        QByteArray color_function =functions.value("color-function").toString().toUtf8();
        QJsonObject domains = obj.value("domains").toObject();
        int x1 = domains.value("x1").toInt();
        int x2 = domains.value("x2").toInt();
        int y1 = domains.value("y1").toInt();
        int y2 = domains.value("y2").toInt();
        int t1 = domains.value("t1").toInt();
        int t2 = domains.value("t2").toInt();
        this->tabWidget->addTab(new Visualize3D(this, 3, x1, x2, y1, y2, t1, t2, pixel_function, color_function), name);
        tabWidget->setCurrentWidget(tabWidget->widget(count));
    }
    }


}

void MainWindow::saveasimage() {
    auto *active = dynamic_cast<SavableWidget *>(tabWidget->currentWidget());
    if (active->savable) {
        auto isSaved = active->saveImage();
        if (!isSaved) showMsgBox("실패", "저장 실패(직접 저장을 취소했거나 잘못된 확장자를 입력)");
        else showMsgBox("성공", "저장 성공");
    }
    else showMsgBox("실패", "무엇을 저장?");
}

void MainWindow::saveproject() {
    auto *active = dynamic_cast<SavableWidget *>(tabWidget->currentWidget());
    if (active->savable) {
        auto isSaved = active->saveProject();
        if (!isSaved) showMsgBox("실패", "저장 실패(직접 저장을 취소했거나 잘못된 확장자를 입력 또는 읽기 전용)");
        else showMsgBox("성공", "저장 성공");
    }
    else showMsgBox("실패", "무엇을 저장?");
}


void MainWindow::saveasimagesequence() {
    auto *active = dynamic_cast<SavableWidget *>(tabWidget->currentWidget());
        if (active->savable) {
        auto isSaved = active->saveImages();
        if (!isSaved) showMsgBox("실패", "저장 실패(직접 저장을 취소했거나 잘못된 확장자를 입력)");
        else showMsgBox("성공", "저장 성공");

    }
        else showMsgBox("실패", "무엇을 저장?");
}