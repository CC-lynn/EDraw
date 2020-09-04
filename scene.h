#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTextStream>
#include "item_info.h"
#include <QColor>
#include "ammeter.h"
#include "capacitance.h"
#include "light.h"
#include "power_e.h"
#include "rect.h"
#include "switch.h"
#include "triangle.h"
#include "voltmeter.h"
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "item_info.h"
#include "algorithem.h"
#include "mygroup.h"
#include "myline.h"
class Scene:public QGraphicsScene
{
public:
    bool saveScene(QFile* file);

    bool loadScene(QFile* file);

    void saveItem(QTextStream& stream);

    void loadItem(QTextStream& stream, QString mode);

    void clearScene();

    //
    void word_save(QTextStream& stream, QGraphicsItemGroup* group);

    QGraphicsItemGroup* word_load(QTextStream& stream);

protected:
    void drawline();  //
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event); // backspace移除item
public:
    bool V = false;  // 伏特表添加
    bool A = false;  // 安培表添加
    bool L = false;  // 电灯泡添加
    bool T = false;  // 二极管添加
    bool R = false;  // 电阻添加
    bool E = false;  // 电源添加
    bool K = false; // 开关添加
    bool U = false; // 电容
    bool S = false; // 滑动变阻器
    bool Seleting = false; //任意选择标志   //
    static int ant;

    QList<mygroup*> item_group;  // 总图元
    QList<mygroup*> ammeter_group; //安培表
    QList<mygroup*> voltmeter_group; // 伏特表
    QList<mygroup*> light_group;  // 小灯泡
    QList<mygroup*> capacitance_group; //电容
    QList<mygroup*> power_group;  // 电源
    QList<mygroup*> rect_group;   // 电阻
    QList<mygroup*> switch_group; // 开关
    QList<mygroup*> triangle_group; // 二极管


    QList<mygroup*> slide_group;
    QPointF pos_s;
    QPointF pos_l;

    void draw(Path* a);//
    void  redraw(Path* a);//

    void dealWithLine();//
    void  dealWithReset();//

    void resetScene();
    void draw_for_reset(Path* a,int leftid,int rightid);
};

#endif // SCENE_H
