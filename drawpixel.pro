RESOURCES += images.qrc

HEADERS += mainwindow.h view.h pixmap.h
SOURCES += main.cpp
SOURCES += mainwindow.cpp view.cpp pixmap.cpp

QT += widgets
qtHaveModule(printsupport): QT += printsupport

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/pixmap
INSTALLS += target
