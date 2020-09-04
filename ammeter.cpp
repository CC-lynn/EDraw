#include "ammeter.h"
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
#include "light.h"
Ammeter::Ammeter()
{

}
void Ammeter::save(QTextStream& stream, mygroup* group)
{
    QPointF pos = group->pos();
    stream << "<g id=\"AMMETER\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" fill-rule=\"evenodd\" stroke-linecap=\"square\" stroke-linejoin=\"bevel\" transform=\"matrix(1,0,0,1,0,0)\">\n\n";
    QList<QGraphicsItem*> item_list = group->childItems();
    QList<QGraphicsItem*>::iterator it = item_list.begin();
    Circle_item* cicle_item = (Circle_item*)it.i->t();
    QRectF rect = cicle_item->rect();
    stream << "<circle cx=\"" << pos.x()+rect.x()+rect.width()/2 << "\" cy=\"" << pos.y()+rect.y()+rect.height()/2 << "\" r=\"" << rect.width()/2 << "\"/>\n\n";

    for(it = item_list.begin()+1; it != item_list.end(); it++){
        QGraphicsLineItem* line_item = (QGraphicsLineItem*)it.i->t();
        QLineF line = line_item->line();
        stream << "<polyline points=\"" << pos.x()+line.x1() << "," << pos.y()+line.y1() << " " << pos.x()+line.x2() << "," << pos.y()+line.y2() << "\" />\n";
    }
    stream << "</g>\n";
}
mygroup* Ammeter::load(QTextStream &stream)
{
    QString line;
    QStringList list;
    mygroup* group = new mygroup;
    do{
        line = stream.readLine();
        if(line.contains("circle")){
            list = line.split("\"", QString::SkipEmptyParts);// " 分割
            Circle_item* item = new Circle_item;
            double cx = list[1].toDouble();
            double cy = list[3].toDouble();
            double r = list[5].toDouble();
            item->setRect(cx-r, cy-r, 2*r, 2*r);
            group->addToGroup(item);
        }
        else if(line.contains("polyline")){
            list = line.split(QRegExp("[\", ]"), QString::SkipEmptyParts);
            double x1 = list[2].toDouble();
            double y1 = list[3].toDouble();
            double x2 = list[4].toDouble();
            double y2 = list[5].toDouble();
            QGraphicsLineItem* line_item = new QGraphicsLineItem(x1,y1,x2,y2);
            group->addToGroup(line_item);
        }
    }while(line != "</g>");
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    |QGraphicsItem::ItemIsSelectable);
    //group->setSelected(true);

    return group;
}
mygroup*Ammeter::drawing()
{
     QPointF point = point_event;
     Circle_item *item = new Circle_item;
     item->setRect(point.x()-25,point.y()-25,30,30);

   //  item->mapToScene(0,0);
     double a = point.x()-10;
     double b = point.y()-10;

     double x1 = a-7.5;
     double y1 = b+7.5;
     double x2 = a;
     double y2 = b-7.5;
     double x3 = a+7.5;
     double x4 = a - 3.75;
     double x5 = a+3.75;
     QGraphicsLineItem * line1 = new QGraphicsLineItem(x1,y1,x2,y2);
    // line1->mapToScene(0,0);

     QGraphicsLineItem * line2 = new QGraphicsLineItem(x3,y1,x2,y2);
    // line2->mapToScene(0,0);

      QGraphicsLineItem * line3 = new QGraphicsLineItem(x4,b,x5,b);
     mygroup * group =new mygroup; //创建组合
    //  scene->addItem(group); //组合添加到场景中
     group->setRealScenePos(point_event.x()-5,point_event.y()-15);   //设置中心点（关于场景坐标）
     QGraphicsLineItem * line5 = new QGraphicsLineItem(a-45,b,a-15,b);
    // line1->mapToScene(0,0);

     QGraphicsLineItem * line6 = new QGraphicsLineItem(a+15,b,a+45,b);
    // line2->mapToScene(0,0);



     group->addToGroup(item); //添加到组合
     group->addToGroup(line2);
     group->addToGroup(line1);
     group->addToGroup(line3);

     group->addToGroup(line5);
     group->addToGroup(line6);
     group->setFlags(QGraphicsItemGroup::ItemIsMovable
                     | QGraphicsItemGroup::ItemIsSelectable
                     | QGraphicsItemGroup::ItemIsFocusable);
     group->setSelected(true);
     pos1 = QPoint(a-45,b);
     pos2 = QPoint(a+45,b);
     group->keyleft= QPoint(point_event.x()-55,point_event.y()-10);
     group->keyright = QPoint(point_event.x()+35,point_event.y()-10);
     return group;
}
