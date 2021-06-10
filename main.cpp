#include <QApplication>
#include "mypaint.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    MyPaint *w = new MyPaint();
    w->setWindowIcon(QIcon(":/png/images/myPainter.png"));
    w->setWindowTitle("电子讨论板");
    w->show();
    return app.exec();
}
