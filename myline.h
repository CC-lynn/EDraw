#ifndef MYLINE_H
#define MYLINE_H
#include <QGraphicsLineItem>
#include <QPoint>
class myLine : public QGraphicsLineItem
{
public:
    myLine(){
        id=count++;}
    int id;
    static int count;
    QPoint realScenePos;
    void setRealPos(qreal x,qreal y);
};

#endif // MYLINE_H
