#include "widget.h"
#include <QTimer>
#include <QDir>
#include <QString>
#include<QApplication>
Widget::Widget(QWidget *parent)
    : QWidget(parent)

{
    this->aboutUI.setpath(":/new/prefix1/image/aboutUInew.png");
    this->aboutapp.setpath(":/new/prefix1/image/aboutappnew.png");
    myplayer =new QMediaPlayer;

    //myplayer->setMedia(QUrl::fromLocalFile("C:\\Users\\Administrator\\Desktop\\untitled\\sound\\mymusic.mp3"));
    myplayer->setMedia(QUrl::fromLocalFile(".././8_26project_last/sound/mymusic.mp3"));
    //设置固定大小
    setFixedSize(700,600);

    //设置图标
    setWindowIcon(QIcon(":/new/prefix1/image/photot1.jpg"));

    //设置标题
    setWindowTitle("电路图入口");

    QSound *startSound = new QSound(":/new/prefix1/sound/11111.wav",this);
    startSound->setLoops(1);
    QSound *startSound2 = new QSound(":/new/prefix1/sound/22222.wav",this);
    startSound->setLoops(1);
    QSound *startSound3 = new QSound(":/new/prefix1/sound/33333.wav",this);
    startSound->setLoops(1);
    QSound *startSound4 = new QSound(":/new/prefix1/sound/44444.wav",this);
    startSound->setLoops(1);

    //开始按钮
    mybutton * startBtn = new mybutton(":/new/prefix1/image/button1.png");
    startBtn->setParent(this);
    startBtn->move( this->width() * 0.5 - startBtn->width() * 1.2 ,this->height() * 0.6 );



    mybutton * startBtn1 = new mybutton(":/new/prefix1/image/aboutapp.png");
    startBtn1->setParent(this);
    startBtn1->move( this->width() * 0.5 - startBtn->width() * 1.2 +201,this->height() * 0.56 );

    mybutton * startBtn2 = new mybutton(":/new/prefix1/image/exit.png");
    startBtn2->setParent(this);
    startBtn2->move( this->width() * 0.5 - startBtn->width() * 1.2 +257,this->height() * 0.73 );

    mybutton * startBtn3 = new mybutton(":/new/prefix1/image/aboutUI.png");
    startBtn3->setParent(this);
    startBtn3->move( this->width() * 0.5 - startBtn->width() * 1.2 +412,this->height() * 0.62 );

    mybutton * startBtn4 = new mybutton(":/new/prefix1/image/aboutmusic.png");
    startBtn4->setParent(this);
    startBtn4->move( this->width() * 0.5 - startBtn->width() * 1.2 +444,this->height() * 0.87 );

    connect(startBtn,&mybutton::clicked,[=]()
    {
        startSound->play(); //开始音效
        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        QTimer::singleShot(500,this,[=](){
          this->hide();
            this->mywin.show();
            myplayer->stop();
        });
        });




    connect(startBtn1,&mybutton::pressed,[=]()
    {
        startBtn1->setIcon(QIcon(":/new/prefix1/image/newaboutapp,png.png"));

        });

    connect(startBtn1,&mybutton::released,[=]()
    {
        startSound->play(); //开始音效
        startBtn1->setIcon(QIcon(":/new/prefix1/image/aboutapp.png"));
        this->hide();
        this->aboutapp.show();
        });

    connect(startBtn2,&mybutton::pressed,[=]()
    {
        startBtn2->setIcon(QIcon(":/new/prefix1/image/newexit.png"));

        });

    connect(startBtn2,&mybutton::released,[=]()
    {
        startSound4->play(); //开始音效
        startBtn2->setIcon(QIcon(":/new/prefix1/image/exit.png"));
        QTimer::singleShot(500,this,[=](){
          this->close();
        });
        });

    connect(startBtn3,&mybutton::pressed,[=]()
    {
        startBtn3->setIcon(QIcon(":/new/prefix1/image/newaboutUI.png"));

        });

    connect(startBtn3,&mybutton::released,[=]()
    {
        startSound3->play(); //开始音效
        startBtn3->setIcon(QIcon(":/new/prefix1/image/aboutUI.png"));
        this->hide();
        this->aboutUI.show();
        });

    connect(startBtn4,&mybutton::pressed,[=]()
    {
        startBtn4->setIcon(QIcon(":/new/prefix1/image/newaboutmusic.png"));

        });

    connect(startBtn4,&mybutton::released,[=]()
    {
        startSound2->play(); //开始音效
        startBtn4->setIcon(QIcon(":/new/prefix1/image/aboutmusic.png"));
        myplayer->stop();
        myplayer->setVolume(60);
        myplayer->play();
        });

    connect(&aboutUI,&mywidget::back,this,&Widget::dealback);
    connect(&aboutapp,&mywidget::back,this,&Widget::dealback);



}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/image/12.webp");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
void Widget::dealback(){
    this->show();
    this->aboutUI.hide();
    this->aboutapp.hide();
}
