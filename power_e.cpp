#include "power_e.h"

Power_E::Power_E()
{

}
void Power_E::save(QTextStream& stream, mygroup* group)
{
    QPointF pos = group->pos();
    stream << "<g id=\"POWER\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" fill-rule=\"evenodd\" stroke-linecap=\"square\" stroke-linejoin=\"bevel\" transform=\"matrix(1,0,0,1,0,0)\">\n\n";

    QList<QGraphicsItem*> item_list = group->childItems();
    QList<QGraphicsItem*>::iterator it;
    for(it = item_list.begin(); it != item_list.end(); it++){
        QGraphicsLineItem* line_item = (QGraphicsLineItem*)it.i->t();
        QLineF line = line_item->line();
        stream << "<polyline points=\"" << pos.x()+line.x1() << "," << pos.y()+line.y1() << " " << pos.x()+line.x2() << "," << pos.y()+line.y2() << "\" />\n\n";
    }
    stream << "</g>\n";
}
mygroup* Power_E::load(QTextStream &stream)
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
    }while(line != "</g>");
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    |QGraphicsItem::ItemIsSelectable);
    //group->setSelected(true);
    return group;
}
mygroup* Power_E::drawing()
{

    QPointF point = point_event;
    QGraphicsLineItem * line1 = new QGraphicsLineItem(point.x()-30,point.y()-20,point.x(),point.y()-20);
    QGraphicsLineItem * line2 = new QGraphicsLineItem(point.x()+10,point.y()-20,point.x()+40,point.y()-20);
    QGraphicsLineItem * line3 = new QGraphicsLineItem(point.x(),point.y()-25,point.x(),point.y()-15);
    QGraphicsLineItem * line4 = new QGraphicsLineItem(point.x()+10,point.y()-10,point.x()+10,point.y()-30);
    mygroup * group =new mygroup; //创建组合

    group->setRealScenePos(point_event.x()-5,point_event.y()-15);   //设置中心点（关于场景坐标）
    //将四条直线添加到组合

    group->addToGroup(line1);
    group->addToGroup(line2);
    group->addToGroup(line3);
    group->addToGroup(line4);
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    | QGraphicsItemGroup::ItemIsSelectable
                    | QGraphicsItemGroup::ItemIsFocusable);

    group->setSelected(true);
    group->keyleft= QPoint(point_event.x()-15,point_event.y()-20);
    group->keyright = QPoint(point_event.x()+40,point_event.y()-20);


    return group;
}
