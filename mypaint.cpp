#include "mypaint.h"
#include <QDebug>
#include <iostream>
#include <cmath>

using namespace std;

MyPaint::MyPaint(QWidget *parent) :
    QMainWindow(parent)
{
     mouseLeftPress = false;//初始鼠标左键未按下
     paintType = 0;//初始为什么都不画
     canDrag = 0; //默认不可拖拽
     isDrag = 0;//默认非拖拽模式
     isDrag2 = 0; //同上
     isZoom = 0;//默认文本框不可缩放，1为可以缩放，2为开始缩放
     haveSetTextArea = false; //默认窗口中没有文本输入框
     _begin = pos();//拖拽的参考坐标，方便计算位移
     isOpenPicture = 0;//初始不打开图片
     textArea = new QTextEdit(this);//初始化文本输入框
     textArea->hide();//隐藏
     this->setGeometry(350,200,800,780);//设置窗体大小、位置
     setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
     this->setStyleSheet("background-color:white;");

    //创建工具栏，并对工具栏进行初始化
    QToolBar *tbar = addToolBar(tr("工具栏"));
    tbar->setMovable(false);//工具栏不可移动
    tbar->setIconSize(QSize(30, 30));//设置动作图标的尺寸
    tbar->setStyleSheet("background-color:rgb(199, 237, 204)");//背景色

    //创建调色板工具栏
    QToolBar *cbar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea, cbar);
    cbar->setMovable(false);//工具栏不可移动
    cbar->setIconSize(QSize(30, 30));
    cbar->setStyleSheet("background-color:rgb(175, 238, 238)");//背景色


    mouseRightPressMenu = new QMenu(this);//创建右键菜单
    mouseRightPressMenu->addAction(tr("保存  \tCtrl+S"), this, SLOT(SavePic()));//添加菜单动作
    mouseRightPressMenu->addAction(tr("退出  \tALT+F4"), this, SLOT(close()));//添加菜单动作
    mouseRightPressMenu->setStyleSheet("background-color:rgb(199,237,204)");//设置背景色

    QAction *openAction = new QAction(tr("&打开"), this);//打开动作
    openAction->setIcon(QIcon(":/png/images/myOpen.png"));//图标
//    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));//热键
    tbar->addAction(openAction);//添加到工具栏

    QAction *saveAction = new QAction(tr("&保存"), this);//保存动作
    saveAction->setIcon(QIcon(":/png/images/mySave.png"));//图标
//    saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));//热键
    tbar->addAction(saveAction);//添加到工具栏

    QAction *saveasAction = new QAction(tr("&另存为"), this);//保存动作
    saveasAction->setIcon(QIcon(":/png/images/mySaveAs.png"));//图标
//    saveasAction->setShortcut(QKeySequence(tr("Ctrl+ALT+S")));//热键
    tbar->addAction(saveasAction);//添加到工具栏

    QAction *lineAction = new QAction(tr("&直线"), this);//直线动作
    lineAction->setIcon(QIcon(":/png/images/myLine.png"));//图标
//    lineAction->setShortcut(QKeySequence(tr("Ctrl+L")));//热键
    tbar->addAction(lineAction);//添加到工具栏

    QAction *linesAction = new QAction(tr("&铅笔"), this);//铅笔动作
    linesAction->setIcon(QIcon(":/png/images/myPencil.png"));//图标
//    linesAction->setShortcut(QKeySequence(tr("Ctrl+P")));//热键
    tbar->addAction(linesAction);//添加到工具栏

    QAction *rectAction = new QAction(tr("&矩形"), this);//矩形动作
    rectAction->setIcon(QIcon(":/png/images/myRectangle.png"));//图标
//    rectAction->setShortcut(QKeySequence(tr("Ctrl+R")));//热键
    tbar->addAction(rectAction);

    QAction *ellipseAction = new QAction(tr("&椭圆"), this);//椭圆动作
    ellipseAction->setIcon(QIcon(":/png/images/myEllipse.png"));//图标
//    ellipseAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
    tbar->addAction(ellipseAction);

    QAction *circleAction = new QAction(tr("&圆"), this);//圆动作
    circleAction->setIcon(QIcon(":/png/images/myCircle.png"));//图标
//    ellipseAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
    tbar->addAction(circleAction);

    QAction *textAction = new QAction(tr("&文字"), this);//文字动作
    textAction->setIcon(QIcon(":/png/images/myTextArea.png"));//图标
//    textAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(textAction);

    QAction *undo = new QAction(tr("&撤销"), this);//撤销
    undo->setIcon(QIcon(":/png/images/myUndo.png"));//图标
    tbar->addAction(undo);

    QAction *getRedAction = new QAction(tr("&红色"), this);//撤销
    getRedAction->setIcon(QIcon(":/png/images/red.png"));//图标
//    this->addToolBarBreak(Qt::TopToolBarArea);
    cbar->addAction(getRedAction);

    QAction *getPinkAction = new QAction(tr("&粉色"), this);//撤销
    getPinkAction->setIcon(QIcon(":/png/images/pink.png"));//图标
    cbar->addAction(getPinkAction);

    QAction *getYellowAction = new QAction(tr("&黄色"), this);//撤销
    getYellowAction->setIcon(QIcon(":/png/images/yellow.png"));//图标
    cbar->addAction(getYellowAction);

    QAction *getBlueAction = new QAction(tr("&蓝色"), this);//撤销
    getBlueAction->setIcon(QIcon(":/png/images/blue.png"));//图标
    cbar->addAction(getBlueAction);

    QAction *getGreenAction = new QAction(tr("&绿色"), this);//撤销
    getGreenAction->setIcon(QIcon(":/png/images/green.png"));//图标
    cbar->addAction(getGreenAction);

    QAction *getItalyAction = new QAction(tr("&斜体"), this);//撤销
    getItalyAction->setIcon(QIcon(":/png/images/italy.png"));//图标
    cbar->addAction(getItalyAction);

    QAction *getBoldAction = new QAction(tr("&加粗"), this);//撤销
    getBoldAction->setIcon(QIcon(":/png/images/bold.png"));//图标
    cbar->addAction(getBoldAction);

    //连接信号与槽函数
    connect(linesAction, SIGNAL(triggered()), this, SLOT(Lines()));
    connect(rectAction, SIGNAL(triggered()), this, SLOT(Rects()));
    connect(ellipseAction, SIGNAL(triggered()), this, SLOT(Ellipses()));
    connect(lineAction, SIGNAL(triggered()), this, SLOT(Line()));
    connect(circleAction, SIGNAL(triggered()), this, SLOT(Circle()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(SavePic()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(OpenPic()));
    connect(textAction, SIGNAL(triggered()), this, SLOT(Texts()));
    connect(textArea, SIGNAL(textChanged()), this, SLOT(AddTexts()));
    connect(undo, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(getRedAction, SIGNAL(triggered(bool)), this, SLOT(getRed()));
    connect(getGreenAction, SIGNAL(triggered(bool)), this, SLOT(getGreen()));
    connect(getBlueAction, SIGNAL(triggered(bool)), this, SLOT(getBlue()));
    connect(getPinkAction, SIGNAL(triggered(bool)), this, SLOT(getPink()));
    connect(getYellowAction, SIGNAL(triggered(bool)), this, SLOT(getYellow()));
}

void MyPaint::paintEvent(QPaintEvent *)
{
    if(isOpenPicture == 0)//不是打开图片的，每一次新建一个空白的画布
    {
        bgPicture = QPixmap(size());//新建pixmap
        bgPicture.fill(Qt::white);//背景色填充为白色
    }
    QPixmap pix = bgPicture;//以bgPicture作为画布
    QPainter p(&pix);//将bgPicture作为画布
    unsigned int i1 = 0,i2 = 0,i3 = 0,i4 = 0,i5 = 0,i6 = 0;//各种图形的索引

    for(int c = 0;c<_shape.size();++c)//控制用户当前所绘图形总数
    {
        if(_shape.at(c) == 1)//线条
        {
              const QVector<QPoint>& line = _lines.at(i1++);//取出一条线条的坐标
              for(int j=0; j<line.size()-1; ++j)//将线条的所有线段描绘出
              {
                  p.drawLine(line.at(j), line.at(j+1));
              }
        }
        else if(_shape.at(c) == 2)//矩形
        {
            QPen pen(_rects.at(i2).getColor());
            p.setPen(pen);
            p.drawRect(_rects.at(i2++));
        }
        else if(_shape.at(c) == 3)//椭圆
        {
            QPen pen(_ellipse.at(i3).getColor());
            p.setPen(pen);
            p.drawEllipse(_ellipse.at(i3++));
        }
        else if(_shape.at(c) == 4)//直线
        {
            p.drawLine(_line.at(i4).topLeft(),_line.at(i4).bottomRight());
            i4++;
        }
        else if(_shape.at(c) == 5)//文本
        {
            p.drawText(_tpoint.at(i5),_text.at(i5));
            i5++;
        }
        else if(_shape.at(c) == 6) //圆形
        {
            QPen pen(_circle.at(i6).getColor());
            p.setPen(pen);
            p.drawEllipse(_circle.at(i6++));
        }
    }
    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0,0, pix);//将pixmap画到窗体
}

void MyPaint::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        if(paintType == 1)//线条(铅笔)
        {
            mouseLeftPress = true;//左键按下标志
            QVector<QPoint> line;//鼠标按下，新的线条开始
            _lines.append(line);//将新线条添加到线条集合
            QVector<QPoint>& lastLine = _lines.last();//拿到新线条
            lastLine.append(e->pos());//记录鼠标的坐标(新线条的开始坐标)
            _shape.append(1);
        }
        else if(paintType == 2)
        {
            mouseLeftPress = true;//左键按下标志
            if(canDrag == 0)
            {
                MyQRect rect;//鼠标按下，矩形开始
                _rects.append(rect);//将新矩形添加到矩形集合
                MyQRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setTopLeft(e->pos());//记录鼠标的坐标(新矩形的左上角坐标)
                _shape.append(2);
            }
            else if (canDrag == 1)
            {
                isDrag2 = 1;
                _begin = _rects.last().center();//拖拽时位移计算是依据矩形正中心的坐标来的
            }
        }
        else if(paintType == 3)//椭圆
        {
            mouseLeftPress = true;//左键按下标志
            if(canDrag == 0)//非拖拽模式
            {
                MyQRect rect;//鼠标按下，椭圆开始
                _ellipse.append(rect);//将新椭圆添加到椭圆集合
                MyQRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
                 _shape.append(3);
            }
            else if(canDrag == 1)//如果在椭圆内按下
            {
                _begin = e->pos();//记录拖拽开始的坐标位置
                isDrag = 1;
            }
        }
        else if(paintType == 4)//直线
        {
            mouseLeftPress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            _line.append(rect);//将新直线添加到直线集合
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _shape.append(4);
        }
        else if(paintType == 5)//文字
        {
            if(isZoom == 0)
            {
                mouseLeftPress = true;//左键按下标志
                update();//触发窗体重绘
                QPoint p;//鼠标按下，文字开始
                _tpoint.append(p);//将文字坐标添加到文字位置集合
                QPoint& lastp = _tpoint.last();//拿到新文字
                lastp = e->pos();//记录鼠标的坐标
                textArea->setGeometry(lastp.x(),lastp.y(),90,90);//设置文本框的位置、大小
                /*
                 * 设置文本框右下角的坐标
                 */
                textAreaRightBottomPoint.setX(textArea->pos().x() + 90);
                textAreaRightBottomPoint.setY(textArea->pos().y() + 90);
                textArea->show();//显示文本输入框
                haveSetTextArea = true; //此时界面中有文本框
                _text.append("");//添加文本到文本集合
                textArea->clear();//因为全局只有一个，所以使用之前要清空
                _shape.append(5);
            }
            else if(isZoom == 1)
            {
                mouseLeftPress = true;//左键按下标志
                isZoom = 2;
            }
        }
        else if(paintType == 6)
        {
            mouseLeftPress = true;//左键按下标志
            if(canDrag == 0)//非拖拽模式
            {
                MyQRect rect;//鼠标按下，椭圆开始
                _circle.append(rect);//将新椭圆添加到椭圆集合
                MyQRect& lastCircle = _circle.last();//拿到新椭圆
                lastCircle.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
                 _shape.append(6);
            }
            else if(canDrag == 1)//如果可拖动
            {
                _begin = e->pos();//记录拖拽开始的坐标位置
                isDrag = 1;
            }
        }
    }
}

void MyPaint::AddTexts()//当输入框文本改变时调用
{
    QString& last = _text.last();//拿到最后一个文本
    last = textArea->toPlainText();//将输入框文本作为文本
}

void MyPaint::mouseMoveEvent(QMouseEvent *e)
{
    if(mouseLeftPress)
    {
        if(paintType == 1)//铅笔画线
        {
            if(_lines.size()<=0) return;//线条集合为空，不画线
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录鼠标的坐标(线条的轨迹)
            update();//触发窗体重绘
        }
        else if(paintType == 2)
        {
            if(isDrag2 == 0)//非拖拽
            {
                MyQRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setBottomRight(e->pos());//更新矩形的右下角坐标
                update();
            }
            else if(isDrag2 == 1)//拖拽模式
            {
                QRect& lastRect = _rects.last();//拿到最后添加的矩形
                if(lastRect.contains(e->pos()))//在矩形的内部
                {
                    int dx = e->pos().x()-_begin.x();//横向移动x
                    int dy = e->pos().y()-_begin.y();//纵向移动y
                    lastRect = lastRect.adjusted(dx,dy,dx,dy);//更新矩形的位置
                    _begin = e->pos();//刷新拖拽点起始坐标
                    update();
                }
            }
            else
            {
                update();
            }
        }
//        else if(paintType == 2)
//        {
//            if(isDrag2 == 0)//非拖拽
//            {
//                QRect& lastRect = _rects.last();//拿到新矩形
//                lastRect.setBottomRight(e->pos());//更新矩形的右下角坐标
//                update();
//            }
//            else if(isDrag2 == 1)//拖拽模式
//            {
//                QRect& lastRect = _rects.last();//拿到最后添加的矩形
//                if(lastRect.contains(e->pos()))//在矩形的内部
//                {
//                    int dx = e->pos().x()-_begin.x();//横向移动x
//                    int dy = e->pos().y()-_begin.y();//纵向移动y
//                    lastRect = lastRect.adjusted(dx,dy,dx,dy);//更新矩形的位置
//                    _begin = e->pos();//刷新拖拽点起始坐标
//                    update();
//                }
//            }
//            else
//            {
//                update();
//            }

//        }
        else if(paintType == 3)
        {
            if(isDrag == 0)//非拖拽
            {
                MyQRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setBottomRight(e->pos());//更新椭圆的右下角坐标
                update();//触发窗体重绘
            }
            else if(canDrag == 1)//拖拽
            {
                QRect& lastEllipse = _ellipse.last();//拿到最后添加的矩形
                if(lastEllipse.contains(e->pos()))//在椭圆内部
                {
                    int dx = e->pos().x()-_begin.x();//横向移动x
                    int dy = e->pos().y()-_begin.y();//纵向移动y
                    lastEllipse = lastEllipse.adjusted(dx,dy,dx,dy);
                    _begin = e->pos();//刷新拖拽点起始坐标
                }
                update();
            }
        }
        else if(paintType == 4)
        {
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            update();//触发窗体重绘
        }
        /*
         * 新增功能，可以缩放文本域窗体大小
         */
        else if(paintType == 5)
        {
            if(isZoom == 2)
            {
                textArea->setGeometry(_tpoint.last().x(), _tpoint.last().y(),
                                      e->pos().x() - _tpoint.last().x(), e->pos().y() - _tpoint.last().y());//设置文本框的位置、大小
                textAreaRightBottomPoint.setX(textArea->pos().x() + e->pos().x() - _tpoint.last().x());
                textAreaRightBottomPoint.setY(textArea->pos().y() + e->pos().y() - _tpoint.last().y());
                updateGeometry(); //刷新文本域界面
            }
        }
        else if(paintType == 6)
        {
            if(isDrag == 0)//非拖拽
            {
                MyQRect& lastCircle = _circle.last();//拿到新椭圆

                //处理圆的右下角坐标
                int dx = e->pos().x() - _circle.last().topLeft().x();
                int dy = e->pos().y() - _circle.last().topLeft().y();

                //让框住椭圆的矩形变成正方形，那么框出来的椭圆一定是圆形
                if(dx <= dy)
                {
                    _circleRightBottomPoint.setX(e->pos().x());
                    _circleRightBottomPoint.setY(_circle.last().topLeft().y() + dx);
                }
                else
                {
                    _circleRightBottomPoint.setX(_circle.last().topLeft().x() + dy);
                    _circleRightBottomPoint.setY(e->pos().y());
                }

                lastCircle.setBottomRight(_circleRightBottomPoint);//更新圆的右下角坐标
                update();//触发窗体重绘
            }
            else if(isDrag == 1)//拖拽
            {
                QRect& lastCircle = _circle.last();//拿到最后添加的矩形
                if(lastCircle.contains(e->pos()))//在圆内部
                {
                    int dx = e->pos().x()-_begin.x();//横向移动x
                    int dy = e->pos().y()-_begin.y();//纵向移动y
                    lastCircle = lastCircle.adjusted(dx,dy,dx,dy);
                    _begin = e->pos();//刷新拖拽点起始坐标
                }
                update();
            }
        }
    }
    else
    {
        if(paintType == 2 && !_rects.isEmpty())
        {
            if(pow(e->pos().x() - _rects.last().center().x(), 2) <= 81 &&
                    pow(e->pos().y() - _rects.last().center().y(), 2) <= 81)
            {
                setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
                canDrag = 1;
            }
            else
            {
                setCursor(Qt::ArrowCursor);//恢复原始光标形状
                canDrag = 0;
            }
        }
//        if(paintType == 2 && !_rects.isEmpty())
//        {
//            if(pow(e->pos().x() - _rects.last().center().x(), 2) <= 81 &&
//                    pow(e->pos().y() - _rects.last().center().y(), 2) <= 81)
//            {
//                setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
//                canDrag = 1;
//            }
//            else
//            {
//                setCursor(Qt::ArrowCursor);//恢复原始光标形状
//                canDrag = 0;
//            }
//        }
        if(paintType == 3 && !_ellipse.isEmpty())
        {
            if(pow(e->pos().x() - _ellipse.last().center().x(), 2) <= 81 &&
                    pow(e->pos().y() - _ellipse.last().center().y(), 2) <= 81)
            {
                setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
                canDrag = 1;
            }
            else
            {
                setCursor(Qt::ArrowCursor);//恢复原始光标形状
                canDrag = 0;
            }
        }
        if(paintType == 6 && !_circle.isEmpty())
        {
            if(pow(e->pos().x() - _circle.last().center().x(), 2) <= 81 &&
                    pow(e->pos().y() - _circle.last().center().y(), 2) <= 81)
            {
                setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
                canDrag = 1;
            }
            else
            {
                setCursor(Qt::ArrowCursor);//恢复原始光标形状
                canDrag = 0;
            }
        }
        if(paintType == 5 && haveSetTextArea)
        {
            //当鼠标移动到输入框右下角时显示可缩放操作
            if(pow(e->pos().x() - textAreaRightBottomPoint.x(), 2) <= 10 &&
                    pow(e->pos().y() - textAreaRightBottomPoint.y(), 2) <= 10)
            {
                setCursor(Qt::SizeFDiagCursor);  //显示可缩放光标
                isZoom = 1;//设置文本框可缩放
            }
            else
            {
                setCursor(Qt::ArrowCursor);//恢复原始光标形状
                isZoom = 0;//出了这个范围就不让缩放
            }
        }
    }
}

void MyPaint::mouseReleaseEvent(QMouseEvent *e)
{
    if(mouseLeftPress)
    {
        if(paintType == 1)
        {
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录线条的结束坐标
            mouseLeftPress = false;//标志左键释放
        }
        else if(paintType == 2)
        {
            MyQRect& lastRect = _rects.last();//拿到新矩形
            if(canDrag == 0)
            {
                if(lastRect.topLeft().x() == e->pos().x() && lastRect.topLeft().y() == e->pos().y())
                {
                    _rects.pop_back();
                    _shape.pop_back();
                }
                else
                {
                    lastRect.setBottomRight(e->pos());//不是拖拽时，更新矩形的右下角坐标
                    update();
                }
            }
            else
            {
                isDrag2 = 0;
                update();
            }
            mouseLeftPress = false;
        }
        else if(paintType == 3)
        {
            MyQRect& lastEllipse = _ellipse.last();//拿到新椭圆
            if(canDrag == 0)
            {
                if(lastEllipse.topLeft().x() == e->pos().x() && lastEllipse.topLeft().y() == e->pos().y())
                {
                    _ellipse.pop_back();
                    _shape.pop_back();
                }
                else
                {
                    lastEllipse.setBottomRight(e->pos());//不是拖拽时，更新椭圆的右下角坐标
                    update();
                }
            }
            else
            {
                isDrag = 0;
                update();
            }
            mouseLeftPress = false;
        }
        else if(paintType == 4)
        {
            QRect& lastLine = _line.last();//线条
            lastLine.setBottomRight(e->pos());//更新矩形的右下角坐标
            mouseLeftPress = false;

        }
        else if(paintType == 5)
        {
            mouseLeftPress = false;
        }
        else if(paintType == 6)
        {
            MyQRect& lastCircle = _circle.last();//拿到新椭圆
            if(canDrag == 0)
            {
                //如果原地点一个点，就不画
                if(lastCircle.topLeft().x() == e->pos().x() && lastCircle.topLeft().y() == e->pos().y())
                {
                    _circle.pop_back();
                    _shape.pop_back();
                }
                else
                {
                    lastCircle.setBottomRight(_circleRightBottomPoint);//固定好圆的右下角坐标
                    isDrag = 0;
                }
            }
            else
            {
                isDrag = 0;
            }
            update();
            mouseLeftPress = false;
        }
    }
}

void MyPaint::Lines()
{
    paintType = 1;//铅笔
    textArea->hide();//文本框隐藏
    haveSetTextArea = false; //界面无文本输入框
}

void MyPaint::Line()
{
    paintType = 4;//直线
    textArea->hide();
    haveSetTextArea = false; //界面无文本输入框
}

void MyPaint::Rects()
{
    paintType = 2;//矩形
    textArea->hide();
    haveSetTextArea = false; //界面无文本输入框
}

void MyPaint::Ellipses()
{
    paintType = 3;//椭圆
    textArea->hide();
    haveSetTextArea = false; //界面无文本输入框
}

void MyPaint::Circle()
{
    paintType = 6;
    textArea->hide();
    haveSetTextArea = false; //界面无文本输入框
}

void MyPaint::Texts()
{
    paintType = 5;//文字
}

void MyPaint::Undo()
{
    if(_shape.size()>0)
    {
        switch(_shape.last())
        {
            case 1: _lines.pop_back();
                    break;
//            case 2: _rects.pop_back();
//                    break;
            case 2: _rects.pop_back();
                    break;
            case 3: _ellipse.pop_back();
                    break;
            case 4: _line.pop_back();
                    break;
            case 6: _circle.pop_back();
                    break;
        }
        _shape.pop_back();
        isDrag = 0;//设置为非拖拽模式
        update();
    }
}

void MyPaint::getRed()
{
    if(_shape.size()>0)
    {
        switch(_shape.last())
        {
            case 2:
            {
                _rects.last().setColor(Qt::red);
                break;
            }
            case 3:
            {
                _ellipse.last().setColor(Qt::red);
                break;
            }
            case 6:
            {
                _circle.last().setColor(Qt::red);
                break;
            }
        }
        update();
    }
    if(haveSetTextArea)
    {
        textArea->setTextColor(Qt::red);
    }
}

void MyPaint::getGreen()
{
    if(_shape.size()>0)
    {
        switch(_shape.last())
        {
//            case 2: _testRects.pop_back();
//                    break;
//            case 3: _ellipse.pop_back();
//                    break;
//            case 6: _circle.pop_back();
//                    break;
            case 2:
            {
                _rects.last().setColor(Qt::green);
                break;
            }
            case 3:
            {
                _ellipse.last().setColor(Qt::green);
                break;
            }
            case 6:
            {
                _circle.last().setColor(Qt::green);
                break;
            }
        }
        update();
    }
}

void MyPaint::getYellow()
{
    if(_shape.size()>0)
    {
        switch(_shape.last())
        {
//            case 2: _testRects.pop_back();
//                    break;
//            case 3: _ellipse.pop_back();
//                    break;
//            case 6: _circle.pop_back();
//                    break;
            case 2:
            {
                _rects.last().setColor(Qt::yellow);
                break;
            }
            case 3:
            {
                _ellipse.last().setColor(Qt::yellow);
                break;
            }
            case 6:
            {
                _circle.last().setColor(Qt::yellow);
                break;
            }
        }
        update();
    }
}

void MyPaint::getPink()
{
    if(_shape.size()>0)
    {
        switch(_shape.last())
        {
//            case 2: _testRects.pop_back();
//                    break;
//            case 3: _ellipse.pop_back();
//                    break;
//            case 6: _circle.pop_back();
//                    break;
            case 2:
            {
                _rects.last().setColor(QColor(255, 192, 203));
                break;
            }
            case 3:
            {
                _ellipse.last().setColor(QColor(255, 192, 203));
                break;
            }
            case 6:
            {
                _circle.last().setColor(QColor(255, 192, 203));
                break;
            }
        }
        update();
    }
}

void MyPaint::getBlue()
{
    if(_shape.size()>0)
    {
        switch(_shape.last())
        {
            case 2:
            {
                _rects.last().setColor(Qt::blue);
                break;
            }
            case 3:
            {
                _ellipse.last().setColor(Qt::blue);
                break;
            }
            case 6:
            {
                _circle.last().setColor(Qt::blue);
                break;
            }
        }
        update();
    }
}

void MyPaint::SavePic()
{
    //弹出文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), "new.jpg", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0)
    {
        textArea->hide();//防止文本输入框显示时，将文本框保存到图片
        QPixmap pixmap(size());//新建窗体大小的pixmap
        QPainter painter(&pixmap);//将pixmap作为画布
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
        this->render(&painter);//将窗体渲染到painter，再由painter画到画布
        pixmap.copy(QRect(0,30,size().width(),size().height()-30)).save(fileName);//不包含工具栏
    }
}

void MyPaint::OpenPic()
{
    //弹出文件打开对话框
    QString picPath = QFileDialog::getOpenFileName(this,tr("打开"),"","Image Files(*.jpg *.png)");
    if(!picPath.isEmpty())//用户选择了文件
    {
        QPixmap pix;
        pix.load(picPath);//加载图片
        QPainter p(&bgPicture);
        p.drawPixmap(0,30,pix);//添加工具栏的空间
        isOpenPicture = 1;//设置文件打开标志
        update();//触发窗体重绘，将图片画到窗体
    }
}

void MyPaint::contextMenuEvent(QContextMenuEvent *)  //右键菜单事件
{
    mouseRightPressMenu->exec(cursor().pos());//在光标位置弹出菜单
}

void MyPaint::keyPressEvent(QKeyEvent *e) //按键事件
{
     //Ctrl+Z撤销
     if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier)
     {
         if(_shape.size()>0)
         {
             switch(_shape.last())
             {
                 case 1: _lines.pop_back();
                         break;
//                 case 2: _rects.pop_back();
//                         break;
                 case 2: _rects.pop_back();
                         break;
                 case 3: _ellipse.pop_back();
                         break;
                 case 4: _line.pop_back();
                         break;
                 case 6: _circle.pop_back();
                         break;
             }
             _shape.pop_back();
             isDrag = 0;//设置为非拖拽模式
             update();
         }
     }
     else if (e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)//保存
     {
        SavePic();//Ctrl+S保存
     }
}
