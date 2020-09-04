#include "algorithem.h"
int Path::count=0;
Path* idealPath(QPoint left,QPoint right)
{
    Path * newpath=new Path;
    if(left.x()==right.x()){
        newpath->path.append(left);
        newpath->path.append(right);
    }
    else if(left.y()==right.y()){
        newpath->path.append(left);
        newpath->path.append(right);
    }
    else{
        QPoint middle(left.x(),right.y());
        newpath->path.append(left);
        newpath->path.append(middle);
        newpath->path.append(right);
    }
    return newpath;
}

//Path* idealPath(QPoint* left,QPoint* right)
//{
//    Path * newpath=new Path;
//    QPoint templeft(left->x(),left->y());
//    QPoint tempright(right->x(),right->y());
//    if(left->x()==right->x()){
//        newpath->path.append(templeft);
//        newpath->path.append(tempright);
//    }
//    else if(left->y()==right->y()){
//        newpath->path.append(templeft);
//        newpath->path.append(tempright);
//    }
//    else{
//        QPoint middle(left->x(),right->y());
//        newpath->path.append(templeft);
//        newpath->path.append(middle);
//        newpath->path.append(tempright);
//    }
//    return newpath;
//}


int Path::size()
{
    return this->path.size();
}
