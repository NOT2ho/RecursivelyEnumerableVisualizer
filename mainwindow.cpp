#include "mainwindow.h"
#include "visualize2D.h"
#include <qdockwidget.h>
#include <qmenubar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("file", this);
    menuBar->addMenu(fileMenu);
    this->setMenuBar(menuBar);

    Visualize2D *vis2d = new Visualize2D(this);

    QDockWidget *dockWidget2d = new QDockWidget(tr("2D visualizer"), this);
    dockWidget2d->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
    dockWidget2d->setWidget(vis2d);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget2d);


}
