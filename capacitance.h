#ifndef U_H
#define U_H
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
class capacitance
{
public:

    void static save(QTextStream& stream, mygroup* group);

    static mygroup* load(QTextStream& stream);

public:
    capacitance();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();
};

#endif // U_H
