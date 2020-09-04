#ifndef SWITCH_H
#define SWITCH_H
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
class Switch
{
public:

    void static save(QTextStream& stream, mygroup* group);

    static mygroup* load(QTextStream& stream);

public:
    Switch();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();
};

#endif // SWITCH_H
