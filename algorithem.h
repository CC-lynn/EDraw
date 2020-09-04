#ifndef ALGORITHEM_H
#define ALGORITHEM_H
#include <QPoint>
#include <QVector>
class Path{
public:
    QVector<QPoint> path;
    int size();
    QVector<int> Lines_in_this_global_number;
    int id;
    static int count;
    bool is_changed=false;
    bool left_is_changed=false;
    bool right_is_changed=false;

};

Path* idealPath(QPoint left,QPoint right);
//Path* idalPath(QPoint* left,QPoint* right);
void outPut();

#endif // ALGORITHEM_H
