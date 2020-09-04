#ifndef VOLTMETER_H
#define VOLTMETER_H
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
class Voltmeter
{
public:

    void static save(QTextStream& stream, mygroup* group);

    static mygroup* load(QTextStream& stream);

public:
    Voltmeter();
    QPoint pos1;
    QPoint pos2;
    QPointF point_event;
    mygroup* drawing();
};

#endif // VOLTMETER_H
