#ifndef SLIDE_RECT_H
#define SLIDE_RECT_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include "item_info.h"
#include <QTextStream>
#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include "item_info.h"
#include <QVector>
#include "mygroup.h"
class Slide_rect
{
public:

    void static save(QTextStream& stream, mygroup* group);

    static mygroup* load(QTextStream& stream);
public:
    Slide_rect();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();

};

#endif // SLIDE_RECT_H
