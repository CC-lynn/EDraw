#include "mygraphicsview.h"
#include    <QMouseEvent>
#include    <QPoint>

void Mygraphicsview::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动事件
//    QPoint  point;
    QPoint point=event->pos(); //QGraphicsView的坐标
    emit mouseMovePoint(point); //释放信号
    QGraphicsView::mouseMoveEvent(event);
}

void Mygraphicsview::mousePressEvent(QMouseEvent *event)
{ //鼠标左键按下事件
    if (event->button()==Qt::LeftButton)
    {
//        QPoint  point;
        QPoint point=event->pos(); //QGraphicsView的坐标
        emit mouseClicked(point);//释放信号
    }
    QGraphicsView::mousePressEvent(event);
}

void Mygraphicsview::mouseDoubleClickEvent(QMouseEvent *event)
{ //鼠标双击事件
    if (event->button()==Qt::LeftButton)
    {
//        QPoint  point;
        QPoint point=event->pos(); //QGraphicsView的坐标
        emit mouseDoubleClick(point);//释放信号
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void Mygraphicsview::keyPressEvent(QKeyEvent *event)
{ //按键事件
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}

Mygraphicsview::Mygraphicsview(QWidget *parent):QGraphicsView(parent)
{

}
