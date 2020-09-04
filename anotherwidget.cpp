#include "anotherwidget.h"

anotherwidget::anotherwidget(QWidget *parent) :
    QWidget(parent)
{

    update();
    setFixedSize(700,600);

    //设置标题
    setWindowTitle("关于程序");
}

anotherwidget::~anotherwidget()
{

}
void anotherwidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/image/aboutUInew.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
