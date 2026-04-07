#include "mainwindow.h"
#include "visualize2D.h"
#include "visualize3D.h"
#include <qdockwidget.h>
#include <qtabwidget.h>
#include <qmenubar.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle(tr("r.e. visualizer"));


    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("file", this);
    QMenu *helpMenu = new QMenu("help", this);
    QAction *saveasimageAct = new QAction("save as image", this);
    QAction *helpAct = new QAction("help..", this);
    QAction *seemoreAct = new QAction("see more..", this);
    menuBar->addMenu(fileMenu);
    connect(helpAct, &QAction::triggered, this, [this](){this->seeHelp();});
    connect(seemoreAct, &QAction::triggered, this, [this](){this->seeSeemore();});

    fileMenu->addAction(saveasimageAct);
    helpMenu->addAction(helpAct);
    helpMenu->addAction(seemoreAct);
    menuBar->addMenu(helpMenu);
    this->setMenuBar(menuBar);

    Visualize2D *vis2d = new Visualize2D(this);
    Visualize3D *vis3d = new Visualize3D(this);

    QTabWidget *tabWidget = new QTabWidget(this);

    tabWidget->addTab(vis2d, tr("2d vis"));
    tabWidget->addTab(vis3d, tr("3d vis"));
    this->setCentralWidget(tabWidget);

    connect(saveasimageAct, &QAction::triggered, this, [this, tabWidget](){this->saveasimage(tabWidget->currentWidget());});


}

void MainWindow::seeHelp() {
    showMsgBox("도움", "JavaScript를 사용하여 함수를 입력하세요. 입출력이 자연수인지, 인자 수가 정확한지를 확인하세요. 하단의 입력창에서 범위를 설정할 수 있습니다.")
}

void MainWindow::seeSeemore() {
    showMsgBox(tr("설명"), "버전: 테스트\n현재는 2차원, 3차원만 있습니다(4차원 이상을 시각화하는(슬라이더를 더 추가해서 2차원 단면을 잔뜩 만드는 것보다 더 좋은) 방법이 있으면 당신이 직접 만드십시오). r.e.set을 도메인으로 정하지 않으면 영원히 값이 안 나오는 것이 설계 의도이며 실제로 그렇게 되는지는 모릅니다(아마 그렇게 될 듯). 더 상세한 도메인을 입력받는 건 아직 안 만들었으니 입력에 주의하세요." );
}

void MainWindow::showMsgBox(QString title, QString text) {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.exec();
}

void MainWindow::saveasimage(QWidget *widget) {
    auto *actived = dynamic_cast<SavableWidget *>(widget);
    if (actived->savable) {
        auto isSaved = actived->saveImage();
        if (!isSaved)
        {
            showMsgBox("실패", "저장 실패");
        }
    }
}