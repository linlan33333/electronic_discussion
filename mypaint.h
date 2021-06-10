#ifndef MYPAINT_H
#define MYPAINT_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>
#include <myqrect.h>

class MyPaint : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyPaint(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void contextMenuEvent(QContextMenuEvent *);//重写菜单事件
    void keyPressEvent(QKeyEvent *e); //重写按键事件
public:
private:
    QString color;
    int mouseLeftPress;//左键按下标志
    int isDrag;//拖拽标志
    int canDrag; //指示是否可以拖拽
    int isDrag2;//测试的拖拽标志
    int paintType;//描绘类型
    int isZoom;  //缩放标志
    bool haveSetTextArea; //界面中是否存在文本输入框
    QMenu *mouseRightPressMenu;//右键菜单

    int isOpenPicture;//打开图片
    QPixmap bgPicture;//画布图片
    QTextEdit *textArea;//文本输入框

public:
    //文本域右下角点的坐标，用来缩放文本域的
    QPoint textAreaRightBottomPoint;
    QVector<QVector<QPoint> > _lines;//线条集合(一条线条可包含多个线段)
//    QVector<MyQRect> _testRects; //实验的矩形集合
    QVector<MyQRect> _rects;//矩形集合
    QVector<MyQRect> _ellipse;//椭圆集合
    QVector<MyQRect> _circle; //圆形集合
    QVector<QRect>  _line;//直线集合
    QVector<QString>  _text;//文字集合
    QVector<QPoint>  _tpoint;//文字位置集合
    QVector<int>  _shape;//图形类型集合，用于撤回功能
    QPoint _circleRightBottomPoint; //用来处理圆的右下角坐标，保证圆的美观性
    QPoint _begin;//鼠标按下坐标、用于最后一个图形移动
signals:

public slots:
    void Lines();//铅笔画线
    void SavePic();//保存图片
    void Rects();//画矩形
    void Ellipses();//画椭圆
    void Circle(); //画圆
    void Line();//画直线
    void OpenPic();//打开图片
    void Texts();//文字
    void AddTexts();//添加文字
    void Undo();//撤销
    void getRed();//染成红色
    void getGreen();//染成绿色
    void getYellow();//染成黄色
    void getPink();//染成粉色
    void getBlue();//染成蓝色
};

#endif // MYPAINT_H
