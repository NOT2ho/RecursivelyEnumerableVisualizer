#ifndef VALUEARRAY2D_H
#define VALUEARRAY2D_H
#include <qjsvalue.h>
#include<vector>
#include <QColor>
#include <QJSEngine>

class valueArray2D
{
private:
    QJSValue f;
    QJSValue cf;
    QJSValue def;
    QJSEngine engine;


public:
    QString s;
    QString cs;
    std::vector<int> dom;
    //std::vector<std::vector<int>> valArr;
    valueArray2D(QString sf, QString sf2, std::vector<int> dom);
    int getValue(int, int);
    QColor getColor(int, int, int);
    QJSValue parse3 (QString);
    QJSValue parse2 (QString);
    QJSValue parse (QString);

};

#endif // VALUEARRAY2D_H
