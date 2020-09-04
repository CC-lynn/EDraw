#include "slide_rect.h"
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
Slide_rect::Slide_rect()
{

}
void Slide_rect::save(QTextStream& stream, mygroup* group)
{
    QPointF pos = group->pos();
    stream << "<g id=\"Rect_Slide\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" fill-rule=\"evenodd\" stroke-linecap=\"square\" stroke-linejoin=\"bevel\" transform=\"matrix(1,0,0,1,0,0)\">\n\n";
    QList<QGraphicsItem*> item_list = group->childItems();
    QList<QGraphicsItem*>::iterator it = item_list.begin();
    for(it = item_list.begin(); it-item_list.begin() < 7; it++){
        QGraphicsLineItem* line_item = (QGraphicsLineItem*)it.i->t();
        QLineF line = line_item->line();
        stream << "<polyline points=\"" << pos.x()+line.x1() << "," << pos.y()+line.y1() << " " << pos.x()+line.x2() << "," << pos.y()+line.y2() << "\" />\n\n";
    }
    Rect_item* rect_item = (Rect_item*)it.i->t();
    QRectF rect = rect_item->rect();
    stream << "<rect_slide x=\"" << pos.x()+rect.x() << "\" y=\"" << pos.y()+rect.y() << "\" width=\"" << rect.width() << "\" height=\"" << rect.height() << "\"/>\n";
    stream << "</g>\n";
}
mygroup* Slide_rect::load(QTextStream &stream)
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
        else if(line.contains("rect_slide")){
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
mygroup* Slide_rect::drawing() // 电阻绘制函数
{
    Rect_item *item = new Rect_item;
    item->setRect(point_event.x()-25,point_event.y()-25,40,20);

    QGraphicsLineItem * line1 = new QGraphicsLineItem (point_event.x()-55,point_event.y()-15,point_event.x()-25,point_event.y()-15);
    QGraphicsLineItem  * line2 = new QGraphicsLineItem (point_event.x()+15,point_event.y()-15,point_event.x()+45,point_event.y()-15);
    QGraphicsLineItem * line3 = new QGraphicsLineItem (point_event.x()-35,point_event.y()-15,point_event.x()-35,point_event.y()-40);\
    QGraphicsLineItem * line4 = new QGraphicsLineItem (point_event.x()-35,point_event.y()-40,point_event.x()-10,point_event.y()-40);
    QGraphicsLineItem * line5 = new QGraphicsLineItem (point_event.x()-10,point_event.y()-40,point_event.x()-10,point_event.y()-25);
    QGraphicsLineItem * line6 = new QGraphicsLineItem (point_event.x()-10,point_event.y()-25,point_event.x()-15,point_event.y()-30);
    QGraphicsLineItem * line7 = new QGraphicsLineItem (point_event.x()-10,point_event.y()-25,point_event.x()-5,point_event.y()-30);
    mygroup * group =new mygroup; //创建组合

    group->setRealScenePos(point_event.x()-5,point_event.y()-15);   //设置中心点（关于场景坐标）


    group->addToGroup(line2);
    group->addToGroup(line1);
    group->addToGroup(line3);
    group->addToGroup(line4);
    group->addToGroup(line5);
    group->addToGroup(line6);
    group->addToGroup(line7);
    group->addToGroup(item);
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    | QGraphicsItemGroup::ItemIsSelectable
                    | QGraphicsItemGroup::ItemIsFocusable);

    group->setSelected(true);
    //连线端点  坐标获取位置信息
    group->keyleft= QPoint(point_event.x()-55,point_event.y()-15);
    group->keyright = QPoint(point_event.x()+45,point_event.y()-15);

    return group;
}
