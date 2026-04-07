#include "valuearray2d.h"
#include <QJSEngine>


QJSValue valueArray2D::parse2 (QString strf) {
    return engine.evaluate("({" + strf + "})").property("main");

}

QJSValue valueArray2D::parse (QString strf) {
    return engine.evaluate("({" + strf + "})").property("main");
}

valueArray2D::valueArray2D (QString s, QString s2, std::vector<int> dom) {
    f = parse2(s);
    cf = parse(s2);
    // for (int i = dom[0]; i < dom[1]; i++){
    //     std::vector<int> a;
    //     for (int j = dom[2]; j < dom[3] ; j++){
    //         QJSValueList lst;
    //         lst << i << j;
    //         a.emplace_back(f.call(lst).toInt());
    //     }
    //     valArr->emplace_back(a);
    // }
}


int valueArray2D::getValue (int a, int b) {
    QJSValueList lst;
    lst << a << b;
    return f.call(lst).toInt();

}



QColor valueArray2D::getColor(int a) {

    QJSValueList lst;
    lst << a;
    return cf.call(lst).toInt();
}