#ifndef AMMETER_H
#define AMMETER_H
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
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
class Ammeter
{
public:

    static void save(QTextStream& stream, mygroup* group);

    static  mygroup * load(QTextStream& stream);

public:
    Ammeter();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();
};

#endif // AMMETER_H
