#include "rect.h"
#include <QGraphicsItemGroup>
#include  <QPen>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QtMath>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
Rect::Rect()
{

}
void Rect::save(QTextStream& stream, mygroup* group)
{
    QPointF pos = group->pos();
    stream << "<g id=\"RECT\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" fill-rule=\"evenodd\" stroke-linecap=\"square\" stroke-linejoin=\"bevel\" transform=\"matrix(1,0,0,1,0,0)\">\n\n";
    QList<QGraphicsItem*> item_list = group->childItems();
    QList<QGraphicsItem*>::iterator it = item_list.begin();
    for(it = item_list.begin(); it-item_list.begin() < 2; it++){
        QGraphicsLineItem* line_item = (QGraphicsLineItem*)it.i->t();
        QLineF line = line_item->line();
        stream << "<polyline points=\"" << pos.x()+line.x1() << "," << pos.y()+line.y1() << " " << pos.x()+line.x2() << "," << pos.y()+line.y2() << "\" />\n\n";
    }
    Rect_item* rect_item = (Rect_item*)it.i->t();
    QRectF rect = rect_item->rect();
    stream << "<rect x=\"" << pos.x()+rect.x() << "\" y=\"" << pos.y()+rect.y() << "\" width=\"" << rect.width() << "\" height=\"" << rect.height() << "\"/>\n";
    stream << "</g>\n";
}
mygroup* Rect::load(QTextStream &stream)
{
    QString line;
    QStringList list;
    mygroup* group = new mygroup;
    do{
        line = stream.readLine();
        if(line.contains("polyline")){
            list = line.split(QRegExp("[\", ]"), QString::SkipEmptyParts);
            double x1 = list[2].toDouble();
            double y1 = list[3].toDouble();
            double x2 = list[4].toDouble();
            double y2 = list[5].toDouble();
            QGraphicsLineItem* line_item = new QGraphicsLineItem(x1,y1,x2,y2);
            group->addToGroup(line_item);
        }
        else if(line.contains("rect")){
            list = line.split(QRegExp("[\", ]"), QString::SkipEmptyParts);
            double x = list[2].toDouble();
            double y = list[4].toDouble();
            double w = list[6].toDouble();
            double h = list[8].toDouble();
            Rect_item* item = new Rect_item;
            item->setRect(x, y, w, h);
            group->addToGroup(item);
        }
    }while(line != "</g>");
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    |QGraphicsItem::ItemIsSelectable);
    //group->setSelected(true);
    return group;
}
mygroup* Rect::drawing() // 电阻绘制函数
{
    Rect_item *item = new Rect_item;
    item->setRect(point_event.x()-25,point_event.y()-25,40,20);

    QGraphicsLineItem * line1 = new QGraphicsLineItem (point_event.x()-55,point_event.y()-15,point_event.x()-25,point_event.y()-15);
    QGraphicsLineItem  * line2 = new QGraphicsLineItem (point_event.x()+15,point_event.y()-15,point_event.x()+45,point_event.y()-15);

    mygroup * group =new mygroup; //创建组合
    group->setRealScenePos(point_event.x()-5,point_event.y()-15);   //设置中心点（关于场景坐标）

    group->addToGroup(line2);
    group->addToGroup(line1);
    group->addToGroup(item);
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                        | QGraphicsItemGroup::ItemIsSelectable
                        | QGraphicsItemGroup::ItemIsFocusable);


    group->setSelected(true);
    //连线端点  坐标获取位置信息
    group->keyleft= QPoint(point_event.x()-55,point_event.y()-15);
    group->keyright = QPoint(point_event.x()+45,point_event.y()-15);
    group->width = group->boundingRect().width();
    group->height = group->boundingRect().height();
    return group;
}


Rect_item::Rect_item(QGraphicsItem *parent):   // 矩形构造函数
    QGraphicsRectItem(parent)
{
      QPen p = pen();
      p.setWidth(1);
      p.setColor(Qt::black);

      setPen(p);

      setBrush(Qt::white);

      setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
}
void Rect_item::mousePressEvent(QGraphicsSceneMouseEvent *event)  //  矩形鼠标按压触发事件
{
    if(event->button()==Qt::LeftButton)
    {
        if(event->modifiers()==Qt::ShiftModifier)
        {
            setSelected(true);
        }
         else if(event->modifiers()==Qt::AltModifier)
        {
            double radius = boundingRect().width()/2.0;
            QPointF topLeft = boundingRect().topLeft();
            m_centerPointF = QPointF(topLeft.x()+pos().x()+radius,topLeft.y()+pos().y()+radius);
            QPointF pos = event->scenePos();
            double dist = sqrt(pow(m_centerPointF.x()-pos.x(),2)+pow(m_centerPointF.y()-pos.y(),2));
            if(dist/radius >0.8)
            {
                m_bResizing = true;
            }
            else {
                m_bResizing = false;
            }
        }else {
              QGraphicsItem::mousePressEvent(event);
              event->accept();
          }
    }else if(event->button()==Qt::RightButton)
    {
        event->ignore();
    }
}
void Rect_item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)     // 矩形鼠标移动事件
{
    if((event->modifiers()==Qt::AltModifier)&&m_bResizing)
    {
        QPointF pos = event->scenePos();
        double dist = sqrt(pow(m_centerPointF.x()-pos.x(), 2) + pow(m_centerPointF.y()-pos.y(), 2));
        setRect(m_centerPointF.x()-this->pos().x()-dist, m_centerPointF.y()-this->pos().y()-dist, dist*2, dist*3);

    }else if(event->modifiers()!=Qt::AltModifier)
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}
void Rect_item::mouseRealeaseEvent(QGraphicsSceneMouseEvent *event)  // 矩形鼠标释放事件
{
    if((event->modifiers()==Qt::AltModifier)&&m_bResizing)
    {
        m_bResizing = false;
    }
    else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}
//int Rect_item::type()const  //矩形计数器
//{
//    return Type;
//}

