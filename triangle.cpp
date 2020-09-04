#include "triangle.h"
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
Triangle::Triangle()
{

}
void Triangle::save(QTextStream& stream, mygroup* group)
{
    QPointF pos = group->pos();
    stream << "<g id=\"TRIANGLE\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" fill-rule=\"evenodd\" stroke-linecap=\"square\" stroke-linejoin=\"bevel\" transform=\"matrix(1,0,0,1,0,0)\">\n\n";
    QList<QGraphicsItem*> item_list = group->childItems();
    QList<QGraphicsItem*>::iterator it = item_list.begin();
    Triangle_item* item = (Triangle_item*)it.i->t();

    stream << "<path d=\"";
    QPolygonF p = item->polygon();
    QVector<QPointF>::iterator it_;
    qreal x, y;
    for(it_ = p.begin(); it_ != p.end(); it_++){
        if(it_ == p.begin()) {stream << "M"; x = it_->x()+pos.x(); y = it_->y()+pos.y();}
        else stream << "L";
        stream << it_->x()+pos.x() << "," << it_->y()+pos.y() << " ";
    }
    stream << "L" << x << "," << y << " \"/>\n\n";
    for(it = item_list.begin()+1; it != item_list.end(); it++){
        QGraphicsLineItem* line_item = (QGraphicsLineItem*)it.i->t();
        QLineF line = line_item->line();
        stream << "<polyline points=\"" << line.x1()+pos.x() << "," << line.y1()+pos.y() << " " << line.x2()+pos.x() << "," << line.y2()+pos.y() << "\" />\n\n";
    }
    stream << "</g>\n";
}
mygroup* Triangle::load(QTextStream &stream)
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
        else if(line.contains("path")){
            list = line.split(QRegExp("[\", LM]"), QString::SkipEmptyParts);
            double x1 = list[4].toDouble();
            double y1 = list[5].toDouble();
            double x2 = list[6].toDouble();
            double y2 = list[7].toDouble();
            double x3 = list[8].toDouble();
            double y3 = list[9].toDouble();
            Triangle_item* item = new Triangle_item;
            QPolygonF p;
            p << QPointF(x1, y1) << QPointF(x2, y2) << QPointF(x3, y3);
            item->setPolygon(p);
            group->addToGroup(item);
        }
    }while(line != "</g>");
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    |QGraphicsItem::ItemIsSelectable);
    //group->setSelected(true);
    return group;
}
mygroup* Triangle::drawing()
{
    Triangle_item *item = new Triangle_item;
    QGraphicsLineItem * line1 = new QGraphicsLineItem(point_event.x()-40,point_event.y(),point_event.x()+40,point_event.y());
    QGraphicsLineItem * line2 = new QGraphicsLineItem(point_event.x()+10,point_event.y()+10,point_event.x()+10,point_event.y()-10);
    QPolygonF p;
    p << QPointF(point_event.x()-10,point_event.y()-10) << QPointF(point_event.x()-10,point_event.y()+10) << QPointF(point_event.x()+10,point_event.y());//三角形三个点的相对坐标
    item->setPolygon(p);
    mygroup * group =new mygroup; //创建组合

    group->setRealScenePos(point_event.x()-5,point_event.y()-15);   //设置中心点（关于场景坐标）
    //将三角形和两条直线添加到组合
    group->addToGroup(item);
    group->addToGroup(line1);
    group->addToGroup(line2);
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    | QGraphicsItemGroup::ItemIsSelectable
                    | QGraphicsItemGroup::ItemIsFocusable);
    group->setSelected(true);
    group->keyleft= QPoint(point_event.x()-40,point_event.y());
    group->keyright = QPoint(point_event.x()+40,point_event.y());
    return group;

}
Triangle_item::Triangle_item(QGraphicsItem *parent):   // 三角形构造函数
    QGraphicsPolygonItem(parent)
{
      QPen p = pen();
      p.setWidth(1);
      p.setColor(Qt::black);

      setPen(p);

      setBrush(Qt::black);

      setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
}
void Triangle_item::mousePressEvent(QGraphicsSceneMouseEvent *event)  //  三角形鼠标按压触发事件
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
void Triangle_item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)     // 三角形鼠标移动事件
{
    if((event->modifiers()==Qt::AltModifier)&&m_bResizing)
    {
        QPointF pos = event->scenePos();
        double dist = sqrt(pow(m_centerPointF.x()-pos.x(), 2) + pow(m_centerPointF.y()-pos.y(), 2));
          QPolygonF polygon;
          polygon << QPointF(m_centerPointF.x()-this->pos().x()-dist,m_centerPointF.y()-this->pos().y()-dist)<<QPointF(m_centerPointF.x()-this->pos().x()-dist,m_centerPointF.y()-this->pos().y()+dist)
                  <<QPointF(m_centerPointF.x()-this->pos().x()+dist,m_centerPointF.y()-this->pos().y()+dist);
          setPolygon(polygon);
    }else if(event->modifiers()!=Qt::AltModifier)
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}
void Triangle_item::mouseRealeaseEvent(QGraphicsSceneMouseEvent *event)  // 三角形鼠标释放事件
{
    if((event->modifiers()==Qt::AltModifier)&&m_bResizing)
    {
        m_bResizing = false;
    }
    else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}
int Triangle_item::type()const  // 三角形计数器
{
    return Type;
}
