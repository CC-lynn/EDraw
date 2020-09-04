#ifndef MYGROUP_H
#define MYGROUP_H
#include <QPoint>
#include <QVector>
#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QKeyEvent>
class mygroup : public QGraphicsItemGroup
{
public:

   mygroup();
   int id;
   QPoint keyleft,keyright,realScenePos;
   QPointF beginPoint,endPoint;  //鼠标移动时起始点和中止点
   QVector <int> lnbor;
   QVector <int> rnbor;
   QVector <int> lnborPaths;
   QVector <int> rnborPaths;
   static bool is_selecting;
   static bool is_single;
   static bool reset;

   bool n =0;
   bool s =0;
   bool w =true;
   bool e=0;

   void setRealScenePos(qreal x,qreal y);
   qreal width;
   qreal height;

protected:

   void keyPressEvent(QKeyEvent *event);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//   void mouseRealeaseEvent(QGraphicsSceneMouseEvent *event);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // MYGROUP_H
