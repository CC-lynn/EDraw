#include "light.h"
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

light::light()
{

}
void light::save(QTextStream& stream, mygroup* group)
{
    QPointF pos = group->pos();
    stream << "<g id=\"LIGHT\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" fill-rule=\"evenodd\" stroke-linecap=\"square\" stroke-linejoin=\"bevel\" transform=\"matrix(1,0,0,1,0,0)\">\n\n";
    QList<QGraphicsItem*> item_list = group->childItems();
    QList<QGraphicsItem*>::iterator it = item_list.begin();
    Circle_item* cicle_item = (Circle_item*)it.i->t();
    QRectF rect = cicle_item->rect();
    stream << "<circle cx=\"" << pos.x()+rect.x()+rect.width()/2 << "\" cy=\"" << pos.y()+rect.y()+rect.height()/2 << "\" r=\"" << rect.width()/2 << "\"/>\n\n";

    for(it = item_list.begin()+1; it != item_list.end(); it++){
        QGraphicsLineItem* line_item = (QGraphicsLineItem*)it.i->t();
        QLineF line = line_item->line();
        stream << "<polyline points=\"" << pos.x()+line.x1() << "," << pos.y()+line.y1() << " " << pos.x()+line.x2() << "," << pos.y()+line.y2() << "\" />\n\n";
    }
    stream << "</g>\n";
}
mygroup* light::load(QTextStream &stream)
{
    QString line;
    QStringList list;
    mygroup* group = new mygroup;
    do{
        line = stream.readLine();
        if(line.contains("circle")){
            list = line.split("\"", QString::SkipEmptyParts);
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
mygroup* light::drawing()
{
    Circle_item *item = new Circle_item;
    item->setRect(point_event.x()-25,point_event.y()-25,30,30);

    item->mapToScene(0,0);
    double a = point_event.x()-17.5;
    double b = point_event.y()-19.5;

    double x1 = a + sqrt(2)*15/2+15/2;
    double y1 = b + sqrt(2)*15/2+15/2;
    double x2 = a - sqrt(2)*15/2+15/2;
    double y2 = b - sqrt(2)*15/2+15/2;


    QGraphicsLineItem * line1 = new QGraphicsLineItem(x1+1,y1+2,x2+1,y2+2);
   // line1->mapToScene(0,0);

    QGraphicsLineItem * line2 = new QGraphicsLineItem(x2+1,y1+2,x1+1,y2+2);
   // line2->mapToScene(0,0);
    QGraphicsLineItem * line3 = new QGraphicsLineItem(a-37,b+10,a-07,b+10);
    QGraphicsLineItem * line4 = new QGraphicsLineItem(a+23,b+10,a+53,b+10);
    mygroup * group =new mygroup; //创建组合

    group->setRealScenePos(point_event.x()-5,point_event.y()-15);   //设置中心点（关于场景坐标）
   //  scene->addItem(group); //组合添加到场景中

    group->addToGroup(item); //添加到组合
    group->addToGroup(line1);
    group->addToGroup(line2);
    group->addToGroup(line3);
    group->addToGroup(line4);
    group->setFlags(QGraphicsItemGroup::ItemIsMovable
                    | QGraphicsItemGroup::ItemIsSelectable
                    | QGraphicsItemGroup::ItemIsFocusable);
    //clearSelection();
    group->setSelected(true);
    group->keyleft= QPoint(point_event.x()-55,point_event.y()-10);
    group->keyright = QPoint(point_event.x()+35,point_event.y()-10);
    return group;

}
Circle_item::Circle_item(QGraphicsItem *parent):   // 圆形构造函数
    QGraphicsEllipseItem(parent)
    {
          QPen p = pen();
          p.setWidth(1);
          p.setColor(Qt::black);

          setPen(p);

          setBrush(Qt::white);

          setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    }
    void Circle_item::mousePressEvent(QGraphicsSceneMouseEvent *event)  //  圆形鼠标按压触发事件
    {
        if(event->button()==Qt::LeftButton)
        {
            if(event->modifiers()==Qt::ShiftModifier)
            {
                setSelected(true);
            }
             else if(event->modifiers()==Qt::AltModifier)  // 放缩
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
    void Circle_item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)     // 圆形鼠标移动事件
    {
        if((event->modifiers()==Qt::AltModifier)&&m_bResizing)
        {
            QPointF pos = event->scenePos();
            double dist = sqrt(pow(m_centerPointF.x()-pos.x(), 2) + pow(m_centerPointF.y()-pos.y(), 2));
            setRect(m_centerPointF.x()-this->pos().x()-dist, m_centerPointF.y()-this->pos().y()-dist, dist*2, dist*2);

        }else if(event->modifiers()!=Qt::AltModifier)
        {
            QGraphicsItem::mouseMoveEvent(event);
        }
    }
    void Circle_item::mouseRealeaseEvent(QGraphicsSceneMouseEvent *event)  // 圆鼠标释放事件
    {
        if((event->modifiers()==Qt::AltModifier)&&m_bResizing)
        {
            m_bResizing = false;
        }
        else {
            QGraphicsItem::mouseReleaseEvent(event);
        }
    }
    int Circle_item::type()const  // 圆形计数器
    {
        return Type;
    }
