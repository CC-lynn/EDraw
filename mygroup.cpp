#include "mygroup.h"
#include "rect.h"
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QtMath>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include "scene.h"

bool mygroup::is_selecting=false;
bool mygroup::is_single=false;
bool mygroup::reset=false;

mygroup::mygroup()
{

}

void mygroup::keyPressEvent(QKeyEvent *event)  //   0，1设定判定标志
{
    qDebug()<<"group key";
    if(event->key()==Qt::Key_1)
    {
        is_selecting = true;
        Item_info::tempList.clear();
        Item_info::tempList.squeeze();
        qDebug() << "has set for 1";
    }
    else if(event->key()==Qt::Key_0)
    {
        Item_info::tempList.clear();
        Item_info::tempList.squeeze();
        is_selecting = false;
        qDebug() << "has set for 0";
    }
    else {
        QGraphicsItem::keyPressEvent(event);
    }
}


void mygroup::mousePressEvent(QGraphicsSceneMouseEvent *event)  //  鼠标按下
{
    if(event->button()==Qt::LeftButton)
    {

        if(is_selecting == true)
        {
            Item_info::tempList.append(this->id);
        }else {
              QGraphicsItem::mousePressEvent(event);
              event->accept();

          }
    }else if(event->button()==Qt::RightButton)
    {
        event->ignore();
    }
    beginPoint=event->scenePos();
    QGraphicsItem::mousePressEvent(event);
}
void mygroup::mouseMoveEvent(QGraphicsSceneMouseEvent *event)     //J 鼠标移动事件
{
    mygroup::reset=true;
    endPoint=event->scenePos();
//    qDebug() << "Yes";
    QGraphicsItem::mouseMoveEvent(event);

}
void mygroup::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  // 鼠标释放事件
{
//    qDebug() << "item release in";
    endPoint=event->scenePos();   //终止点坐标
    QPoint *newleft,*newright;                                 //重新计算关键点坐标
    newleft=new QPoint(keyleft.x()+endPoint.x()-beginPoint.x(),keyleft.y()+endPoint.y()-beginPoint.y());
    newright=new QPoint(keyright.x()+endPoint.x()-beginPoint.x(),keyright.y()+endPoint.y()-beginPoint.y());
    this->setRealScenePos(this->scenePos().x()+endPoint.x()-beginPoint.x(),this->scenePos().y()+endPoint.y()-beginPoint.y());
  //  设置item的位置(scenePos)

    keyleft=*newleft;
    keyright=*newright;


    for(int i=0;i<lnborPaths.size();i++){  //设置左邻域的路径的端点坐标，打开标记
        int a=lnborPaths[i];
        Item_info::allPaths[a]->is_changed=true;
        QPoint* newPoint= new QPoint;
        newPoint->setX(keyleft.x());
        newPoint->setY(keyleft.y());
        Item_info::fromRight[a] = newPoint;
        Item_info::allPaths[a]->right_is_changed=true;

    }
    for(int i=0;i<rnborPaths.size();i++){
        int a=rnborPaths[i];
        Item_info::allPaths[a]->is_changed=true;
        QPoint* newPoint= new QPoint;
        newPoint->setX(keyright.x());
        newPoint->setY(keyright.y());
        Item_info::fromLeft[a] = newPoint;
        Item_info::allPaths[a]->left_is_changed=true;
    }
    QGraphicsItem::mouseReleaseEvent(event);

//   qDebug() << "item release out";
}
int Rect_item::type()const  //矩形计数器
{
    return Type;
}




void mygroup::setRealScenePos(qreal x,qreal y)
{
    this->realScenePos.setX(x);
    this->realScenePos.setY(y);
}
