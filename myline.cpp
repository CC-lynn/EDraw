#include "myline.h"
int myLine::count=0;


void myLine::setRealPos(qreal x,qreal y)
{
   realScenePos.setX(x);
   realScenePos.setY(y);
}
