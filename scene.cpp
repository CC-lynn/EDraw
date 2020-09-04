#include "scene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTextStream>
#include <QDebug>
#include "rect.h"
#include"light.h"
#include"triangle.h"
#include "item_info.h"
#include "switch.h"
#include "capacitance.h"
#include "power_e.h"
#include "ammeter.h"
#include "voltmeter.h"
#include "mainwindow.h"
#include "slide_rect.h"
#include "scene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "rect.h"
#include "item_info.h"
#include <QDebug>
#include "new_info.h"
int Scene::ant = 0;

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if(mygroup::is_selecting == true)
    {
        dealWithLine();
    }
    if(!event->isAccepted())
    {
        if(event->button()==Qt::LeftButton)
        {
            if(R) //电阻
            {
                QPointF point = event->scenePos();
              //  QPointF point = MainWindow::pointScene;
                Rect *rect = new Rect;
                rect->point_event = point;

                mygroup * group =  rect->drawing();

                group->setSelected(true);
                addItem(group);

                // 放入两端点
                group->id=ant++;
                Item_info::allList.append(group);
                item_group.push_back(group);
                rect_group.push_back(group);
                R = false;
            }
            else if(L) //小灯泡
            {
                QPointF point = event->scenePos();
                light *Light = new light;
                Light->point_event= point;
                mygroup * group = Light->drawing();
                group->setSelected(true);
                addItem(group);
                //放入两端点
                group->id=ant++;
                Item_info::allList.append(group);
                item_group.push_back(group);
                light_group.push_back(group);
                L=false;
            }
            else if(T) // 二极管
            {
                QPointF point = event->scenePos();
                Triangle *triangle = new Triangle;
                triangle->point_event= point;
                mygroup *group =triangle->drawing();
                group->setSelected(true);
                addItem(group);
                //放入两端点
                group->id=ant++;
                Item_info::allList.append(group);
                item_group.push_back(group);
                triangle_group.push_back(group);
                T=false;
            }
            else if(K) // 开关
           {
                 QPointF point = event->scenePos();
                 Switch *s = new Switch;
                 s->point_event = point;
                 mygroup *group = s->drawing();
                 group->setSelected(true);
                 addItem(group);
                 // 放入两点
                 group->id=ant++;
                 Item_info::allList.append(group);
                 item_group.push_back(group);
                 switch_group.push_back(group);
                 K=false;
            }
            else if(U) //电容
             {
               QPointF point = event->scenePos();
               capacitance *u = new capacitance;
               u->point_event = point;
               mygroup *group = u->drawing();
               group->setSelected(true);
               addItem(group);
               //放入两端点
               group->id=ant++;
               Item_info::allList.append(group);
                item_group.push_back(group);
                capacitance_group.push_back(group);
                U = false;
             }
            else if(E) // 电源
            {
                QPointF point = event->scenePos();
                Power_E *p = new Power_E;
                p->point_event = point;
                mygroup *group = p->drawing();
                group->setSelected(true);
                addItem(group);
                //放入两端点
                group->id=ant++;
                Item_info::allList.append(group);
                item_group.push_back(group);
                power_group.push_back(group);
                E = false;
            }
            else if(A)
            {
                QPointF point = event->scenePos();
                Ammeter *a = new Ammeter;
                a->point_event = point;
                mygroup *group = a->drawing();
                group->setSelected(true);
                addItem(group);
                //放入两端点
                group->id=ant++;
                Item_info::allList.append(group);
                item_group.push_back(group);
                ammeter_group.push_back(group);
                A = false;
            }
            else if(V)
             {
                QPointF point = event->scenePos();
                Voltmeter *v = new Voltmeter;
                v->point_event = point;
                mygroup *group = v->drawing();
                group->setSelected(true);
                addItem(group);
                //放入两端点
                group->id=ant++;
                Item_info::allList.append(group);
                item_group.push_back(group);
                voltmeter_group.push_back(group);
                V = false;
               }
            else if(S)
            {
                QPointF point = event->scenePos();
               //  QPointF point = MainWindow::pointScene;
                Slide_rect *rect = new  Slide_rect;
                rect->point_event = point;

                mygroup * group =  rect->drawing();

                group->setSelected(true);
                addItem(group);

                // 放入两端点
                group->id=ant++;
                Item_info::allList.append(group);
                item_group.push_back(group);
                slide_group.push_back(group);
                S = false;
            }
             else if(event->button()==Qt::RightButton) // 光标下是否有item  // 尝试一下  有可能对于其他图形 无用
             {
                    QGraphicsItem *itemtoremove = NULL;
                    foreach(QGraphicsItem *item,items(event->scenePos()))
                    {
                        if(item->type()>=QGraphicsItem::UserType+1&&item->type()<=QGraphicsItem::UserType+5)
                        {
                            itemtoremove = item;
                            break;
                        }
                    }
                    if(itemtoremove!=NULL)
                    {
                        removeItem(itemtoremove);
                    }
              }
        }
    }

}
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) // 场景 鼠标移动触发事件
{
    QGraphicsScene::mouseMoveEvent(event);
}
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if(mygroup::reset){
        dealWithReset();
    }
}
void Scene::keyPressEvent(QKeyEvent *event) //  场景 鼠标点击事件
{
    qDebug()<<"scene key";
    if(event->key()==Qt::Key_Backspace) // 删除所有选中的item
    {
        while(!selectedItems().isEmpty())
        {
            mygroup* group = (mygroup*)selectedItems().front();
            if(ammeter_group.contains(group))
                ammeter_group.removeOne(group);
            else if(capacitance_group.contains(group))
                capacitance_group.removeOne(group);
            else if(light_group.contains(group))
                light_group.removeOne(group);
            else if(power_group.contains(group))
                power_group.removeOne(group);
            else if(rect_group.contains(group))
                rect_group.removeOne(group);
            else if(switch_group.contains(group))
                switch_group.removeOne(group);
            else if(triangle_group.contains(group))
                triangle_group.removeOne(group);
            else if(voltmeter_group.contains(group))
                voltmeter_group.removeOne(group);
            else if(slide_group.contains(group))
                slide_group.removeOne(group);
            if(item_group.contains(group))
                item_group.removeOne(group);
            removeItem(selectedItems().front());
        }

    }
    else if(event->key()==Qt::Key_A)
    {
        R = false;
        U = false;
        E = false;
        A = true;
        V = false;
        S = false;
        K = false;
        T = false;
        L = false;
    }
    else if(event->key()==Qt::Key_V)
    {
        V = true;
        R = false;
        U = false;
        E = false;
        A = false;
        S = false;
        K = false;
        T = false;
        L = false;
    }
    else if(event->key()==Qt::Key_R)
    {
        R = true;

        U = false;
        E = false;
        A = false;
        V = false;
        S = false;
        K = false;
        T = false;
        L = false;
    }
    else if(event->key()==Qt::Key_L)
    {
        L = true;
        R = false;
        U = false;
        E = false;
        A = false;
        V = false;
        S = false;
        K = false;
        T = false;
    }
    else if(event->key()==Qt::Key_T)
    {
        T = true;
        R = false;
        U = false;
        E = false;
        A = false;
        V = false;
        S = false;
        K = false;

        L = false;
    }
    else if(event->key()==Qt::Key_E)
    {
        E = true;
        R = false;
        U = false;
      //  E = false;
        A = false;
        V = false;
        S = false;
        K = false;
        T = false;
        L = false;
    }
    else if(event->key()==Qt::Key_K)
    {
        K = true;
        R = false;
        U = false;
        E = false;
        A = false;
        V = false;
        S = false;
       // K = false;
        T = false;
        L = false;
    }
    else if(event->key()==Qt::Key_U)
    {
        U = true;
        R = false;
       // U = false;
        E = false;
        A = false;
        V = false;
        S = false;
        K = false;
        T = false;
        L = false;
    }
    else if(event->key()==Qt::Key_S)
    {
        S = true;
        R = false;
        U = false;
        E = false;
        A = false;
        V = false;
       // S = false;
        K = false;
        T = false;
        L = false;
    }
    else if(event->key()==Qt::Key_O){
        output();
    }
    else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void Scene::saveItem(QTextStream& stream)   //  保存所有
{
    QList<mygroup*>::iterator it;
    for(it = ammeter_group.begin(); it != ammeter_group.end(); it++){
        Ammeter::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y() << " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = capacitance_group.begin(); it != capacitance_group.end(); it++){
        capacitance::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = light_group.begin(); it != light_group.end(); it++){
        light::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = power_group.begin(); it != power_group.end(); it++){
        Power_E::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = rect_group.begin(); it != rect_group.end(); it++){
        Rect::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = switch_group.begin(); it != switch_group.end(); it++){
        Switch::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = triangle_group.begin(); it != triangle_group.end(); it++){
        Triangle::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = voltmeter_group.begin(); it != voltmeter_group.end(); it++){
        Voltmeter::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }
    for(it = slide_group.begin(); it != slide_group.end(); it++)
    {
        Slide_rect::save(stream, it.i->t());
        mygroup * group = *it;
        stream << group->keyleft.x() << " " << group->keyleft.y()<< " "
        << group->keyright.x() << " " << group->keyright.y()
        << " " << group->id << "\n";
        for(int j=0;j<group->lnbor.size();j++){
            stream <<group->lnbor[j] << " ";
        }
        stream << "\n";
        for(int j=0;j<group->rnbor.size();j++){
            stream <<group->rnbor[j] << " ";
        }
        stream << "\n";
    }


}
void Scene::loadItem(QTextStream& stream, QString mode)
{
//    Item_info::allList.clear();
//    Item_info::allList.squeeze();
    mygroup* group;
    QString line;
    QStringList list;
    if(mode == "A"){
        qDebug() << "Load Ammeter...";
        group = Ammeter::load(stream);
        ammeter_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Ammeter Successfully!";
        group->id=id;
    }
    else if(mode == "C"){
        qDebug() << "Load Capacitance...";
        group = capacitance::load(stream);
        capacitance_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Capacitance Successfully!";
        group->id=id;
    }
    else if(mode == "L"){
        qDebug() << "Load Light...";
        group = light::load(stream);
        light_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Light Successfully!";
        group->id=id;
    }
    else if(mode == "P"){
        qDebug() << "Load Power...";
        group = Power_E::load(stream);
        power_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Power Successfully!";
        group->id=id;
    }
    else if(mode == "R"){
        qDebug() << "Load Rect...";
        group = Rect::load(stream);
        rect_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Rect Successfully!";
        group->id=id;
    }
    else if(mode == "S"){
        qDebug() << "Load Switch...";
        group = Switch::load(stream);
        switch_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Switch Successfully!";
        group->id=id;
    }
    else if(mode == "T"){
        qDebug() << "Load Triangle...";
        group = Triangle::load(stream);
        triangle_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Triangle Successfully!";
        group->id=id;
    }
    else if(mode == "V"){
        qDebug() << "Load Voltmeter...";
        group = Voltmeter::load(stream);
        voltmeter_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Voltmeter Successfully!";
        group->id=id;
    }
    else if(mode == "W"){
        qDebug() << "Load Word...";
        group = Slide_rect::load(stream);
        slide_group.push_back(group);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        double x1 = list[0].toDouble();
        double y1 = list[1].toDouble();
        double x2 = list[2].toDouble();
        double y2 = list[3].toDouble();
        int id = list[4].toInt();
        New_info * n = new New_info;
        n->id = id;
        n->left = QPoint(x1,y1);
        n->right = QPoint(x2,y2);
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->lnbor.push_back(list[i].toInt());
        }
        line = stream.readLine();
        list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++)
        {
            n->rnbor.push_back(list[i].toInt());
        }

        Item_info::new_info.push_back(n);
        qDebug() << "Load Word Successfully!";
    }
    addItem(group);
    Item_info::allList.append(group);
}
bool Scene::saveScene(QFile* file)
{
    QTextStream stream(&(*file));
    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    stream << "<svg width=\"" << this->width() << "mm\" height=\"" << this->height() << "mm\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"  version=\"1.2\" baseProfile=\"tiny\">\n";
    stream << "<title>SVG Generator Example Drawing</title>\n";
    stream << "<desc>An SVG drawing created by the SVG Generator Example provided with Qt.</desc>\n";
    stream << "<defs>\n</defs>\n\n";

    saveItem(stream);

    stream << "\n</svg>";
    return true;
}
void Scene::clearScene()
{
    clear();
    ammeter_group.clear();
    capacitance_group.clear();
    light_group.clear();
    power_group.clear();
    rect_group.clear();
    switch_group.clear();
    triangle_group.clear();
    voltmeter_group.clear();
    slide_group.clear();

}
bool Scene::loadScene(QFile* file)
{
    Item_info::allList.clear();
    Item_info::allList.squeeze();
    QTextStream stream(&(*file));
    QString line;
    clearScene();
    while(!stream.atEnd()){
        line = stream.readLine();
        if(line.contains("<g")){
            loadItem(stream, (QString)line[7]);
        }
        if(line == "</svg>") break;
    }
    resetScene();
    return true;
}


void Scene::draw(Path* a)    //画出路径 ,此函数功能十分复杂
{

//    Item_info::fromLeft.append(new QPoint(0,0));
//    Item_info::fromRight.append(new QPoint(0,0));
    Item_info::allList[Item_info::tempList[0]]->lnbor.append(Item_info::tempList[1]);
    Item_info::allList[Item_info::tempList[1]]->rnbor.append(Item_info::tempList[0]);

    if(a->size()==2){


       myLine* newLine=new myLine;
       newLine->setFlags(QGraphicsItemGroup::ItemIsMovable
                         | QGraphicsItemGroup::ItemIsSelectable
                         | QGraphicsItemGroup::ItemIsFocusable);

       newLine->setLine(a->path[0].x(),a->path[0].y(),a->path[1].x(),a->path[1].y());

       newLine->setRealPos((a->path[0].x()+a->path[1].x())/2,(a->path[0].y()+a->path[1].y())/2 );



       addItem(newLine);
       Item_info::allLines.append(newLine);

       a->Lines_in_this_global_number.append(newLine->id);

       Item_info::fromRight.append(new QPoint(a->path[0].x(),a->path[0].y()));
       Item_info::fromLeft.append(new QPoint(a->path[a->size()-1].x(),a->path[a->size()-1].y()));

    }
    else if(a->size()==3){
                                                                                        //      画
        myLine* Line1=new myLine;                                                       //      两   （一折线）
        myLine* Line2=new myLine;                                                       //      条

        Line1->setFlags(QGraphicsItemGroup::ItemIsMovable
                        | QGraphicsItemGroup::ItemIsSelectable
                        | QGraphicsItemGroup::ItemIsFocusable);
        Line2->setFlags(QGraphicsItemGroup::ItemIsMovable
                        | QGraphicsItemGroup::ItemIsSelectable
                        | QGraphicsItemGroup::ItemIsFocusable);


        Line1->setLine(a->path[0].x(),a->path[0].y(),a->path[1].x(),a->path[1].y());        //      线
        Line2->setLine(a->path[1].x(),a->path[1].y(),a->path[2].x(),a->path[2].y());        //      并
        Line1->setRealPos( (a->path[0].x()+a->path[1].x())/2,(a->path[0].y()+a->path[1].y())/2 );
        Line2->setRealPos( (a->path[2].x()+a->path[1].x())/2,(a->path[2].y()+a->path[1].y())/2 );
        addItem(Line1);                                                                 //      储
        addItem(Line2);                                                                 //      存
                                                                                        //      在


        Item_info::allLines.append(Line1);                                              //      全
        Item_info::allLines.append(Line2);                                              //      局
        Item_info::fromRight.append(new QPoint(a->path[0].x(),a->path[0].y()));
        Item_info::fromLeft.append(new QPoint(a->path[a->size()-1].x(),a->path[a->size()-1].y()));


 //       qDebug() <<"lines id" << Line1->id << " " << Line2->id;
        a->Lines_in_this_global_number.append(Line1->id);                                //      变     此两行
        a->Lines_in_this_global_number.append(Line2->id);
                                                                                         //      量     记录线的ID
    }
                                       //    路径，并
    a->id=a->count++;                         //    记录其ID

    int k=a->id;                                               //
    int index1=Item_info::tempList.at(0);                            //
    int index2=Item_info::tempList.at(1);                            //

    Item_info::allList[index1]->lnborPaths.append(k);                //    记录两个图元所连接的
    Item_info::allList[index2]->rnborPaths.append(k);                //    路径的ID，并将路径加入静态变量
    Item_info::allPaths.append(a);

  //  qDebug() << "global size: "<<a->Lines_in_this_global_number.size();


    Item_info::tempList.clear();
    Item_info::tempList.squeeze();
    mygroup::is_selecting = false;
    //qDebug() << "draw leave";
}

void Scene::dealWithLine()   //画线准备函数，负责画线判定未满时的准备以及画线进入
{
    if(Item_info::tempList.size()==2){
        Path* bridge;
        bridge=idealPath(Item_info::allList.at(Item_info::tempList[0])->keyleft,Item_info::allList.at(Item_info::tempList[1])->keyright);
        draw(bridge);
    }
}

void Scene::dealWithReset()  //整体变线函数
{
    for(int i=0;i<Item_info::allPaths.size();i++){    //对每一个路径进行计算

        if(Item_info::allPaths.at(i)->is_changed==true){    //如果改变标志已开


output();
            QPoint* fromleft=Item_info::fromLeft[i];        //修改后的左点
            QPoint* fromright=Item_info::fromRight[i];      //修改后的右点
            QPoint* realleft= new QPoint;
            realleft->setX(Item_info::allPaths[i]->path.at(Item_info::allPaths[i]->size()-1).x());
            realleft->setY(Item_info::allPaths[i]->path.at(Item_info::allPaths[i]->size()-1).y());
            QPoint* realright =new QPoint;
            realright->setX(Item_info::allPaths[i]->path.at(0).x());
            realright->setY(Item_info::allPaths[i]->path.at(0).y());
qDebug() << fromleft->x() << " " <<fromleft->y()<<" "<<fromright->x() << " " <<fromright->y();
qDebug() << realleft->x() << " " <<realleft->y()<<" "<<realright->x() << " " <<realright->y();
            if(Item_info::allPaths.at(i)->left_is_changed==true&&Item_info::allPaths.at(i)->right_is_changed==true){
                Item_info::allPaths.at(i)->left_is_changed=false;
                Item_info::allPaths.at(i)->right_is_changed=false;
                Path* tempPath = idealPath(*fromright,*fromleft);

                Item_info::allPaths[i]->path.clear();                           //清理路径
                Item_info::allPaths[i]->path.squeeze();

                for(int j=0;j<tempPath->path.size();j++){                       //重设路径
                    Item_info::allPaths.at(i)->path.append(QPoint(0,0));
                    Item_info::allPaths.at(i)->path[j].setX(tempPath->path[j].x());
                    Item_info::allPaths.at(i)->path[j].setY(tempPath->path[j].y());
                }
                for(int j=0;j<Item_info::allPaths[i]->Lines_in_this_global_number.size();j++){   //去线
                    removeItem(Item_info::allLines.at(Item_info::allPaths[i]->Lines_in_this_global_number[j]));
                    delete Item_info::allLines.at(Item_info::allPaths[i]->Lines_in_this_global_number[j]);
                }
                redraw(tempPath);
                Item_info::allPaths.at(i)->Lines_in_this_global_number.clear();
                Item_info::allPaths.at(i)->Lines_in_this_global_number.squeeze();
                for(int j=0;j<tempPath->Lines_in_this_global_number.size();j++){
                    Item_info::allPaths.at(i)->Lines_in_this_global_number.append(tempPath->Lines_in_this_global_number[j]);
                }
            }

            else if(Item_info::allPaths.at(i)->left_is_changed==true&&Item_info::allPaths.at(i)->right_is_changed==false){
                Item_info::allPaths.at(i)->left_is_changed=false;
                Path* tempPath = idealPath(*realright,*fromleft);

                Item_info::allPaths[i]->path.clear();                           //清理路径
                Item_info::allPaths[i]->path.squeeze();

                for(int j=0;j<tempPath->path.size();j++){                       //重设路径
                    Item_info::allPaths.at(i)->path.append(QPoint(0,0));
                    Item_info::allPaths.at(i)->path[j].setX(tempPath->path[j].x());
                    Item_info::allPaths.at(i)->path[j].setY(tempPath->path[j].y());
                }

                for(int j=0;j<Item_info::allPaths[i]->Lines_in_this_global_number.size();j++){   //去线
                    removeItem(Item_info::allLines.at(Item_info::allPaths[i]->Lines_in_this_global_number[j]));
                    delete Item_info::allLines.at(Item_info::allPaths[i]->Lines_in_this_global_number[j]);
                }
                redraw(tempPath);
                Item_info::allPaths.at(i)->Lines_in_this_global_number.clear();
                Item_info::allPaths.at(i)->Lines_in_this_global_number.squeeze();
                for(int j=0;j<tempPath->Lines_in_this_global_number.size();j++){
                    Item_info::allPaths.at(i)->Lines_in_this_global_number.append(tempPath->Lines_in_this_global_number[j]);
                }
            }

            else if(Item_info::allPaths.at(i)->left_is_changed==false&&Item_info::allPaths.at(i)->right_is_changed==true){
                Item_info::allPaths.at(i)->right_is_changed=false;
                Path* tempPath = idealPath(*fromright,*realleft);

                Item_info::allPaths[i]->path.clear();                           //清理路径
                Item_info::allPaths[i]->path.squeeze();

                for(int j=0;j<tempPath->path.size();j++){                       //重设路径
                    Item_info::allPaths.at(i)->path.append(QPoint(0,0));
                    Item_info::allPaths.at(i)->path[j].setX(tempPath->path[j].x());
                    Item_info::allPaths.at(i)->path[j].setY(tempPath->path[j].y());
                }
                for(int j=0;j<Item_info::allPaths[i]->Lines_in_this_global_number.size();j++){   //去线
                    removeItem(Item_info::allLines.at(Item_info::allPaths[i]->Lines_in_this_global_number[j]));
                    delete Item_info::allLines.at(Item_info::allPaths[i]->Lines_in_this_global_number[j]);
                }
                redraw(tempPath);
                Item_info::allPaths.at(i)->Lines_in_this_global_number.clear();
                Item_info::allPaths.at(i)->Lines_in_this_global_number.squeeze();
                for(int j=0;j<tempPath->Lines_in_this_global_number.size();j++){
                    Item_info::allPaths.at(i)->Lines_in_this_global_number.append(tempPath->Lines_in_this_global_number[j]);
                }

            }
            else{
            }

            Item_info::allPaths.at(i)->is_changed==false;


        }
        qDebug() <<endl<<endl;
    }

    mygroup::reset=false;

}


void Scene::redraw(Path *a)  //画线，修改
{


    if(a->size()==2){


       myLine* newLine=new myLine;
       newLine->setFlags(QGraphicsItemGroup::ItemIsMovable
                         | QGraphicsItemGroup::ItemIsSelectable
                         | QGraphicsItemGroup::ItemIsFocusable);

       newLine->setLine(a->path[0].x(),a->path[0].y(),a->path[1].x(),a->path[1].y());

       newLine->setRealPos((a->path[0].x()+a->path[1].x())/2,(a->path[0].y()+a->path[1].y())/2 );



       addItem(newLine);
       Item_info::allLines.append(newLine);
       a->Lines_in_this_global_number.clear();
       a->Lines_in_this_global_number.squeeze();
       a->Lines_in_this_global_number.append(newLine->id);
    }
    else if(a->size()==3){

        myLine* Line1=new myLine;
        myLine* Line2=new myLine;

        Line1->setFlags(QGraphicsItemGroup::ItemIsMovable
                        | QGraphicsItemGroup::ItemIsSelectable
                        | QGraphicsItemGroup::ItemIsFocusable);
        Line2->setFlags(QGraphicsItemGroup::ItemIsMovable
                        | QGraphicsItemGroup::ItemIsSelectable
                        | QGraphicsItemGroup::ItemIsFocusable);


        Line1->setLine(a->path[0].x(),a->path[0].y(),a->path[1].x(),a->path[1].y());
        Line2->setLine(a->path[1].x(),a->path[1].y(),a->path[2].x(),a->path[2].y());
        Line1->setRealPos( (a->path[0].x()+a->path[1].x())/2,(a->path[0].y()+a->path[1].y())/2 );
        Line2->setRealPos( (a->path[2].x()+a->path[1].x())/2,(a->path[2].y()+a->path[1].y())/2 );
        addItem(Line1);
        addItem(Line2);



        Item_info::allLines.append(Line1);
        Item_info::allLines.append(Line2);

        a->Lines_in_this_global_number.clear();
        a->Lines_in_this_global_number.squeeze();
        a->Lines_in_this_global_number.append(Line1->id);
        a->Lines_in_this_global_number.append(Line2->id);

    }


}


void Scene::draw_for_reset(Path *a,int leftid,int rightid)
{
//    qDebug() <<a->path[0].x()<<" " << a->path[0].y() <<" " <<a->path[a->size()-1].x()<<" "<<a->path[a->size()-1].y();
    if(a->size()==2){


       myLine* newLine=new myLine;
       newLine->setFlags(QGraphicsItemGroup::ItemIsMovable
                         | QGraphicsItemGroup::ItemIsSelectable
                         | QGraphicsItemGroup::ItemIsFocusable);

       newLine->setLine(a->path[0].x(),a->path[0].y(),a->path[1].x(),a->path[1].y());

       newLine->setRealPos((a->path[0].x()+a->path[1].x())/2,(a->path[0].y()+a->path[1].y())/2 );



       addItem(newLine);
       Item_info::allLines.append(newLine);

       a->Lines_in_this_global_number.append(newLine->id);

       Item_info::fromRight.append(new QPoint(a->path[0].x(),a->path[0].y()));
       Item_info::fromLeft.append(new QPoint(a->path[a->size()-1].x(),a->path[a->size()-1].y()));

    }
    else if(a->size()==3){
                                                                                        //      画
        myLine* Line1=new myLine;                                                       //      两   （一折线）
        myLine* Line2=new myLine;                                                       //      条

        Line1->setFlags(QGraphicsItemGroup::ItemIsMovable
                        | QGraphicsItemGroup::ItemIsSelectable
                        | QGraphicsItemGroup::ItemIsFocusable);
        Line2->setFlags(QGraphicsItemGroup::ItemIsMovable
                        | QGraphicsItemGroup::ItemIsSelectable
                        | QGraphicsItemGroup::ItemIsFocusable);


        Line1->setLine(a->path[0].x(),a->path[0].y(),a->path[1].x(),a->path[1].y());        //      线
        Line2->setLine(a->path[1].x(),a->path[1].y(),a->path[2].x(),a->path[2].y());        //      并
        Line1->setRealPos( (a->path[0].x()+a->path[1].x())/2,(a->path[0].y()+a->path[1].y())/2 );
        Line2->setRealPos( (a->path[2].x()+a->path[1].x())/2,(a->path[2].y()+a->path[1].y())/2 );
        addItem(Line1);                                                                 //      储
        addItem(Line2);                                                                 //      存
                                                                                        //      在


        Item_info::allLines.append(Line1);                                              //      全
        Item_info::allLines.append(Line2);                                              //      局
        Item_info::fromRight.append(new QPoint(a->path[0].x(),a->path[0].y()));
        Item_info::fromLeft.append(new QPoint(a->path[a->size()-1].x(),a->path[a->size()-1].y()));


        qDebug() <<"lines id" << Line1->id << " " << Line2->id;
        a->Lines_in_this_global_number.append(Line1->id);                                //      变     此两行
        a->Lines_in_this_global_number.append(Line2->id);
                                                                                         //      量     记录线的ID
    }
                                              //    路径，并
                                              //    记录其ID
    qDebug() <<"has done here";
    a->id=a->count++;
    int k=a->id;                                               //

    Item_info::allList[leftid]->lnborPaths.append(k);                //    记录两个图元所连接的
    Item_info::allList[rightid]->rnborPaths.append(k);                //    路径的ID，并将路径加入静态变量
    Item_info::allPaths.append(a);

    mygroup::is_selecting = false;
}


void Scene::resetScene(){
    myLine::count=0;                           //置零
    Path::count=0;

    Item_info::fromLeft.clear();               //清理
    Item_info::fromLeft.squeeze();
    Item_info::fromRight.clear();
    Item_info::fromRight.squeeze();

    Item_info::tempList.clear();
    Item_info::tempList.squeeze();
    Item_info::allLines.clear();
    Item_info::allLines.squeeze();
    Item_info::allPaths.clear();
    Item_info::allPaths.squeeze();

    mygroup* tempgroup;
    for(int i=0;i<Item_info::allList.size()-1;i++){
        for(int j=i;j<Item_info::allList.size()-1;j++){
            if(Item_info::allList[j+1]->id<Item_info::allList[j]->id)  {
                tempgroup=Item_info::allList[j];
                Item_info::allList[j]=Item_info::allList[j+1];
                Item_info::allList[j+1]=tempgroup;
            }
        }
    }


    for(int i=0;i<Item_info::new_info.size();i++){
        int index=Item_info::new_info[i]->id;
        int x1=Item_info::new_info[i]->left.x();
        int y1=Item_info::new_info[i]->left.y();

        Item_info::allList[index]->keyleft=QPoint(x1,y1);

        Item_info::allList[index]->keyleft.setY(Item_info::new_info[i]->left.y());

        Item_info::allList[index]->keyright.setX(Item_info::new_info[i]->right.x());
        Item_info::allList[index]->keyright.setY(Item_info::new_info[i]->right.y());

        Item_info::allList[index]->id=Item_info::new_info[i]->id;

        Item_info::allList[index]->is_selecting=false;
        Item_info::allList[index]->reset=false;



        Item_info::allList[index]->lnbor.clear();
        Item_info::allList[index]->lnbor.squeeze();
        Item_info::allList[index]->rnbor.clear();
        Item_info::allList[index]->rnbor.squeeze();
        for(int j=0;j<Item_info::new_info[i]->lnbor.size();j++){
            Item_info::allList[index]->lnbor.append(Item_info::new_info[i]->lnbor[j]);
        }

        for(int j=0;j<Item_info::new_info[i]->rnbor.size();j++){
            Item_info::allList[index]->rnbor.append(Item_info::new_info[i]->rnbor[j]);
        }
    }
    for(int i=0;i<Item_info::allList.size()-1;i++){    //轮画

        for(int j=0;j<Item_info::allList[i]->lnbor.size();j++){
//            qDebug() <<"has done here" << times++ <<"i and j"<<i <<j;
            if(Item_info::allList.at(Item_info::allList[i]->lnbor[j])->id > Item_info::allList[i]->id){

            Path* bridge=new Path;
            bridge=idealPath(Item_info::allList[i]->keyleft,Item_info::allList.at(Item_info::allList[i]->lnbor[j])->keyright);
            draw_for_reset(bridge,Item_info::allList[i]->id,Item_info::allList.at(Item_info::allList[i]->lnbor[j])->id);
            }
        }
        for(int j=0;j<Item_info::allList[i]->rnbor.size();j++){
//            qDebug() <<"has done here" << times++ <<"i and j"<<i <<j;
            if(Item_info::allList.at(Item_info::allList[i]->rnbor[j])->id > Item_info::allList[i]->id){

            Path* bridge=new Path;
            bridge=idealPath(Item_info::allList.at(Item_info::allList[i]->rnbor[j])->keyleft,Item_info::allList[i]->keyright);
            draw_for_reset(bridge,Item_info::allList.at(Item_info::allList[i]->rnbor[j])->id,Item_info::allList[i]->id);
            }
        }
    }

    Scene::ant=Item_info::allList.size();
}
