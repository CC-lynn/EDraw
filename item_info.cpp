//#include "item_info.h"

//Item_info::Item_info()
//{

//}
#include "item_info.h"

QVector<New_info*> Item_info::new_info;

QVector<QPoint*> Item_info::fromLeft;
QVector<QPoint*> Item_info::fromRight;


QVector<mygroup*>  Item_info::allList;
QVector<int>  Item_info::tempList;
QVector<myLine*> Item_info::allLines;
QVector<Path*> Item_info::allPaths;


Item_info::Item_info()
{

}

void output(){
    qDebug() <<"Debug begin at this line:";

    qDebug() << "allLines(myLine*):" <<Item_info::allLines.size();
    for(int i=0;i<Item_info::allLines.size();i++){
        qDebug() << Item_info::allLines[i]->id <<": " <<
            Item_info::allLines[i]->realScenePos.x() << " " <<Item_info::allLines[i]->realScenePos.y();
    }


    qDebug() << "fromLeft(QPoint*):" <<Item_info::fromLeft.size();
    for(int i=0;i<Item_info::fromLeft.size();i++){
        qDebug() << Item_info::fromLeft[i]->x() <<"    "<< Item_info::fromLeft[i]->y();
    }


    qDebug() << "fromRight(QPoint*):" <<Item_info::fromRight.size();
    for(int i=0;i<Item_info::fromRight.size();i++){
        qDebug() << Item_info::fromRight[i]->x() <<"    "<< Item_info::fromRight[i]->y();
    }



    qDebug() << "allPaths(Path*):" <<Item_info::allPaths.size();
    for(int i=0;i<Item_info::allPaths.size();i++){
        qDebug() << "path:" << Item_info::allPaths[i]->path.size();
        for(int j=0;j<Item_info::allPaths[i]->size();j++){
            qDebug() << Item_info::allPaths[i]->path[j].x() << Item_info::allPaths[i]->path[j].y();
        }
        qDebug() << "id:" << Item_info::allPaths[i]->id;
        qDebug() << "line_in_global_number:" << Item_info::allPaths[i]->Lines_in_this_global_number.size();
        for(int j=0;j<Item_info::allPaths[i]->Lines_in_this_global_number.size();j++){
            qDebug() <<Item_info::allPaths[i]->Lines_in_this_global_number[j];
        }
    }


        qDebug() << "templist(int*):" <<Item_info::tempList.size();
        for(int i=0;i<Item_info::tempList.size();i++){
            qDebug() << Item_info::tempList[i];
        }


    qDebug() << "allList(mygroup*):" <<Item_info::allList.size();
    for(int i=0;i<Item_info::allList.size();i++){
        qDebug() << "keyleft and key right:" << Item_info::allList[i]->keyleft.x()<<" "<<Item_info::allList[i]->keyleft.y()
                 << " " <<Item_info::allList[i]->keyright.x()<< " " <<Item_info::allList[i]->keyright.y();

        qDebug() << "id:" << Item_info::allList[i]->id;
        qDebug() << "l and r neibour paths id:" << endl << "left:";
        for(int j=0;j<Item_info::allList[i]->lnborPaths.size();j++){
            qDebug() <<Item_info::allList[i]->lnborPaths[j];
        }
        qDebug() <<"right:";
        for(int j=0;j<Item_info::allList[i]->rnborPaths.size();j++){
            qDebug() <<Item_info::allList[i]->rnborPaths[j];
        }
    }
    qDebug() <<"allinfo(new_info*):" <<Item_info::new_info.size();
        for(int i=0;i<Item_info::new_info.size();i++){
            qDebug() <<"left:";
            qDebug()<<Item_info::new_info[i]->left.x()<<" " <<Item_info::new_info[i]->left.y();
            qDebug() << "right";
            qDebug()<<Item_info::new_info[i]->right.x()<<" " <<Item_info::new_info[i]->right.y();
            qDebug() <<"id" <<Item_info::new_info[i]->id;
            qDebug()<<"leftnbors";
            for(int j=0;j<Item_info::new_info[i]->lnbor.size();j++){
                qDebug()<<Item_info::new_info[i]->lnbor[j];
            }
            qDebug()<<"rightnbors";
            for(int j=0;j<Item_info::new_info[i]->rnbor.size();j++){
                qDebug()<<Item_info::new_info[i]->rnbor[j];
            }

        }


    //以上经检测符合要求




}
