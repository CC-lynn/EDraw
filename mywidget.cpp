#include "mywidget.h"

mywidget::mywidget(QWidget *parent) :
    QWidget(parent)
{
    mybutton * startBtn = new mybutton(":/new/prefix1/image/back.png");
    startBtn->setParent(this);
    startBtn->move( this->width() * 0.73  ,this->height() * 0.96 );
    update();
    connect(startBtn,&mybutton::clicked,this,&mywidget::sendslot);
    setFixedSize(700,600);

    //设置标题
    setWindowTitle("关于程序");
}

mywidget::~mywidget()
{

}
void mywidget::paintEvent(QPaintEvent *event){
    painter= new QPainter(this);
    pix.load(path1);

    painter->drawPixmap(0,0,this->width(),this->height(),pix);
}
void mywidget::setpath(QString path)
{
    path1=path;
}
void mywidget::sendslot(){
    emit back();
}
