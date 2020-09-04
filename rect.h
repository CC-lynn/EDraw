#ifndef RECT_H
#define RECT_H
#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include <QTextStream>
#include "item_info.h"

class Rect
{
public:

    void static save(QTextStream& stream, mygroup* group);

    static mygroup* load(QTextStream& stream);

public:
    Rect();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();


};


class Rect_item:public QGraphicsRectItem
{
public:
    int id;
    QPoint keyleft,keyright;
    Rect_item(QGraphicsItem *parent=0);
    enum { Type = UserType + 4 };
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

#endif // RECT_H
