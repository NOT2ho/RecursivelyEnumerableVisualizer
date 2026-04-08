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
    : QMainWindow{parent}
{
    setWindowTitle(tr("r.e. visualizer"));


    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *windowMenu = new QMenu("window", this);
    QMenu *fileMenu = new QMenu("file", this);
    QMenu *helpMenu = new QMenu("help", this);
    QAction *saveasimageAct = new QAction("save image", this);
    QAction *loadprojectAct = new QAction("load project", this);
    QAction *saveasimagesequenceAct = new QAction("save image sequence", this);

    QAction *saveprojectAct = new QAction("save project", this);
    QAction *helpAct = new QAction("help..", this);
    QAction *seemoreAct = new QAction("see more..", this);

    QAction *add2dtabAct = new QAction("add 2d tab", this);
    QAction *add3dtabAct = new QAction("add 3d tab", this);
    menuBar->addMenu(fileMenu);
    connect(helpAct, &QAction::triggered, this, [this](){this->seeHelp();});
    connect(seemoreAct, &QAction::triggered, this, [this](){this->seeSeemore();});

    fileMenu->addAction(saveasimageAct);

    fileMenu->addAction(saveasimagesequenceAct);
    fileMenu->addAction(saveprojectAct);
    fileMenu->addSeparator();
    fileMenu->addAction(loadprojectAct);
    helpMenu->addAction(helpAct);
    helpMenu->addAction(seemoreAct);
    windowMenu->addAction(add2dtabAct);
    windowMenu->addAction(add3dtabAct);

    menuBar->addMenu(windowMenu);
    menuBar->addMenu(helpMenu);
    this->setMenuBar(menuBar);

    Visualize2D *vis2d = new Visualize2D(this);
    Visualize3D *vis3d = new Visualize3D(this);

    tabWidget = new QTabWidget(this);
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
}

void MainWindow::seeHelp() {
    showMsgBox("도움", "JavaScript를 사용하여 함수를 입력하세요. 입출력이 자연수인지, 인자 수가 정확한지를 확인하세요. 하단의 입력창에서 범위를 설정할 수 있습니다.");
}

void MainWindow::seeSeemore() {
    showMsgBox(tr("설명"), "버전: 테스트 v0.04081131\n현재는 2차원, 3차원만 있습니다(4차원 이상을 시각화하는(슬라이더를 더 추가해서 2차원 단면을 잔뜩 만드는 것보다 더 좋은) 방법이 있으면 당신이 직접 만드십시오). r.e.set을 도메인으로 정하지 않으면 도메인 아닌 곳에서 멈춰서 영원히 값이 안 나오는 것이 설계 의도이며 실제로 그렇게 되는지는 모릅니다(아마 그렇게 될 듯). 더 상세한 도메인을 입력받는 건 아직 안 만들었으니 입력에 주의하세요." );
}

void MainWindow::showMsgBox(QString title, QString text) {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
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
        showMsgBox("실패", "당신 잘못"); }

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