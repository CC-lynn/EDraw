//#ifndef ITEM_INFO_H
//#define ITEM_INFO_H
//#include <QGraphicsItem>
//#include <QPoint>
//#include <QPointF>

//class Item_info
//{
//public:
//    Item_info();
//    QGraphicsItemGroup *item;
//    int id;
//    QPoint pos1;
//    QPoint pos2;
//};

//#endif // ITEM_INFO_H
#ifndef ITEM_INFO_H
#define ITEM_INFO_H
#include <QGraphicsItem>
#include <QPoint>
#include <QPointF>
#include "mygroup.h"
#include <QVector>
#include "scene.h"
#include "myline.h"
#include "algorithem.h"
#include <QDebug>
#include "new_info.h"
class Item_info
{
public:
    Item_info();

    static QVector<QPoint*> fromLeft;
    static QVector<QPoint*> fromRight;


    static QVector<mygroup*> allList;
    static QVector<int> tempList;
    static QVector<myLine*> allLines;
    static QVector<Path*> allPaths;
    static QVector<New_info*> new_info;

};






void output();





#endif // ITEM_INFO_H
