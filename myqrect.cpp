#include "myqrect.h"
#include "qmainwindow.h"

MyQRect::MyQRect() : QRect()
{
    this->rectColor = Qt::black;
}

void MyQRect::setColor(QColor color)
{
    this->rectColor = color;
}

QColor MyQRect::getColor() const
{
    return rectColor;
}
