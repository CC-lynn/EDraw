#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class anotherwidget : public QWidget
{
    Q_OBJECT

public:
    explicit anotherwidget(QWidget *parent = nullptr);
    ~anotherwidget();


private:

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYWIDGET_H
