#ifndef VALUEARRAY3D_H
#define VALUEARRAY3D_H
#include <qjsvalue.h>
#include<vector>
#include <QColor>
#include <QJSEngine>

class valueArray3D
{
private:
    QJSValue f;
    QJSValue cf;
    QJSEngine engine;


public:
    QString s;
    QString cs;
    std::vector<int> dom;
    std::vector<std::vector<int>> valArr;
    valueArray3D(QString sf, QString sf2, std::vector<int> dom);
    int getValue(int, int, int);
    QColor getColor(int);
    QJSValue parse2 (QString);
    QJSValue parse (QString);

};

#endif // VALUEARRAY3D_H
