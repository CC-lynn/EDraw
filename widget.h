#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mybutton.h"
#include <QPainter>
#include <QPixmap>
#include <QSound>
#include <QMediaPlayer>
#include "mywidget.h"
#include "mainwindow.h"

#include "anotherwidget.h"
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *);
    QMediaPlayer* myplayer;

    mywidget aboutapp,aboutUI;
    MainWindow mywin;
    void dealback();
private:

};
#endif // WIDGET_H
