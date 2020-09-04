#ifndef NEW_INFO_H
#define NEW_INFO_H

#include <QPoint>
#include <QVector>
class New_info
{
public:
    New_info();
    int id;
    QPoint left;
    QPoint right;
    QVector<int> lnbor;
    QVector<int> rnbor;
};

#endif // NEW_INFO_H
