#include "valuearray3d.h"
#include <QJSEngine>


QJSValue valueArray3D::parse2 (QString strf) {
    return engine.evaluate("({" + strf + "})").property("main");

}

QJSValue valueArray3D::parse (QString strf) {
    return engine.evaluate("({" + strf + "})").property("main");
}

valueArray3D::valueArray3D (QString s, QString s2) {
    f = parse2(s);
    cf = parse(s2);
}


int valueArray3D::getValue (int a, int b, int c) {
    QJSValueList lst;
    lst << a << b << c;
    return f.call(lst).toInt();

}


QColor valueArray3D::getColor(int a) {

    QJSValueList lst;
    lst << a;
    return cf.call(lst).toInt();
}