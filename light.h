#ifndef LIGHT_H
#define LIGHT_H
#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include <QTextStream>
#include "item_info.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include "item_info.h"
#include <QVector>
#include "mygroup.h"
class light
{
public:

    void static save(QTextStream& stream, mygroup* group);

    static mygroup* load(QTextStream& stream);

public:
    light();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();
};

class Circle_item:public QGraphicsEllipseItem
{
public:
    Circle_item(QGraphicsItem *parent=0);
    enum { Type = UserType + 5 };
    // shift 左键 ：进行选择 alt 放缩
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // alt 拖拽  进行缩放 移动
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mouseRealeaseEvent(QGraphicsSceneMouseEvent *event);


    int type() const;
    QPointF m_centerPointF;
private:

    bool m_bResizing;
};
#endif // LIGHT_H
