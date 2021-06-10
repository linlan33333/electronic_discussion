#ifndef MYQRECT_H
#define MYQRECT_H
#include <QMainWindow>

class MyQRect : public QRect
{
public:
    MyQRect();
    void setColor(QColor color);
    QColor getColor() const;

private:
    QColor rectColor;
};

#endif // MYQRECT_H
