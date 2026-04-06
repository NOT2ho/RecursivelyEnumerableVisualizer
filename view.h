#ifndef View_H
#define View_H

#include <QFrame>
#include <QGraphicsView>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE


class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    void changeName(QString name);
    QGraphicsView *graphicsView;

public slots:
    void zoomIn();
    void zoomOut();
    void zoomInBy(int level);
    void zoomOutBy(int level);


private slots:
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void togglePointerMode();
    void print();


private:
    QLabel *label;
    QLabel *label2;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *printButton;
    QToolButton *resetButton;
    QSlider *zoomSlider;
};


#endif // View_H

