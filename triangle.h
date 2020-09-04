#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include <QTextStream>
#include <QTextStream>
#include "item_info.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include "item_info.h"
#include <QVector>
#include "mygroup.h"
class Triangle
{
public:

    void static save(QTextStream& stream, mygroup* group);

    static mygroup* load(QTextStream& stream);

public:
    Triangle();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();
};
class Triangle_item:public QGraphicsPolygonItem
{
public:
    Triangle_item(QGraphicsItem *parent=0);
    enum { Type = UserType + 3 };
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
#endif // TRIANGLE_H
