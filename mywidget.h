#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "mybutton.h"
class mywidget : public QWidget
{
    Q_OBJECT

public:
    explicit mywidget(QWidget *parent = nullptr);
    ~mywidget();
    void setpath(QString path);
    QPainter* painter;
    QPixmap pix;
    QString path1;
    void sendslot();
private:
signals:
    void back();
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYWIDGET_H
