#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QGraphicsView>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QScreen>
#include "light.h"
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene;
    ui->graphicsView->setScene(scene);
    setWindowIcon(QIcon(":/icon/timg (1).png"));
    scene->setSceneRect(QGuiApplication::primaryScreen()->geometry());
    setWindowTitle("EDraw");
//    setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);
}
//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    int x = event->x();
//    int y = event->y();
//    qDebug() << x << y << endl;
//}
MainWindow::~MainWindow()
{
    delete ui;
}
//void MainWindow::on_mouseMovePoint(QPoint point)
//{
//    pointScene = ui->widget->mapToScene(point);
//}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/icon/background2.jpg"));

}
void MainWindow::closeEvent(QCloseEvent *event)
{ //窗口关闭时询问是否退出
   QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "是否保存该电路图？",
                      QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                      QMessageBox::No);

    if (result==QMessageBox::Yes)
       {
         event->accept();
         on_actionSave_triggered();
       }
    else if(result==QMessageBox::No)
           {
             event->accept();
           }
        else
        {
            event->ignore();
        }
}

void MainWindow::on_actionBigger_triggered()//放大
{
    int cnt=scene->selectedItems().count();
        if (cnt==1)
        {
            QGraphicsItem   *item;

            item=scene->selectedItems().at(0);
            mygroup *group = (mygroup*)item;
           // qDebug() << item->x()   <<  item->y();

            QPointF center = item->boundingRect().center();
            item->setTransformOriginPoint(center);

            item->setScale(0.1+item->scale()); // 改变完成 扩大到1.1倍
            double x = item->boundingRect().width();
            group->mapToScene(group->boundingRect().center());
            group->keyleft.setX(group->keyleft.x()-x*0.04);
            group->keyright.setX(group->keyright.x()+x*0.055);
           // group->width = group->width*0.9;
           // group->height = group->height*0.9;
            qDebug() << item->pos() << item->scenePos();

           // group->keyleft.setX(x+xf*1.1);
            //group->keyright.setX(x2+xf*1.1);
        }
//        else
//           ui->widget->scale(1.1,1.1);
}

void MainWindow::on_action_smaller_triggered()//缩小
{
    int cnt=scene->selectedItems().count();
        if (cnt==1)
        {
            QGraphicsItem   *item;
            item=scene->selectedItems().at(0);
            mygroup *group = (mygroup*)item;
            QPointF center = item->boundingRect().center();
            qreal width = group->width;
           // qreal height = group->height;
//            if(scene->switch_group.contains(group))
//            {
//                center.setY(center.y()-height/2);
//            }
//            else if(scene->slide_group.contains(group))
//            {

//            }
//            else
//           {

            item->setTransformOriginPoint(center);
            item->setScale(item->scale()-0.1);

            group->mapToScene(group->boundingRect().center());
            group->keyleft.setX(group->keyleft.x()+width*0.08);
            group->keyright.setX(group->keyright.x()-width*0.05);  // Y 值也改变了，仍需要修改
            group->width = group->width*0.9;
            group->height = group->height*0.9;
            qDebug() << width  << group->height ;
//           }
        }
        //else
            //ui->View->scale(0.9,0.9);
}

void MainWindow::on_action_turnleft_triggered()//逆时针旋转30度
{
    int cnt=scene->selectedItems().count();
        if (cnt==1)
        {
            QGraphicsItem* item=scene->selectedItems().at(0);
            QPointF center = item->boundingRect().center();
            item->setTransformOriginPoint(center);
            item->setRotation(-90+item->rotation());
            mygroup *group = (mygroup*)item;
            int width = group->width;
           // int height = group->height;
            if(group->n)   // 左点 上
            {
                group->keyright.setY(group->keyright.y()-width/2);
                group->keyright.setX(group->keyright.x()+width/2);
                group->keyleft.setY(group->keyleft.y()+width/2);
                group->keyleft.setX(group->keyleft.x()-width/2);
                group->n = false;
                group->w = true;
            }
            else if(group->s) // 左点下
            {
                group->keyright.setY(group->keyright.y()+width/2);
                group->keyright.setX(group->keyright.x()-width/2);
                group->keyleft.setY(group->keyleft.y()-width/2);
                group->keyleft.setX(group->keyleft.x()+width/2);
                group->e = true;
                group->s = false;
            }
            else if(group->e) // 左点 右
            {
                group->keyright.setY(group->keyright.y()+width/2);
                group->keyright.setX(group->keyright.x()+width/2);
                group->keyleft.setY(group->keyleft.y()-width/2);
                group->keyleft.setX(group->keyleft.x()-width/2);
                group->n = true;
                group->e = false;
            }
            else if(group->w) // 左点 左
            {
                group->keyright.setY(group->keyright.y()-width/2);
                group->keyright.setX(group->keyright.x()-width/2);
                group->keyleft.setY(group->keyleft.y()+width/2);
                group->keyleft.setX(group->keyleft.x()+width/2);
                group->s = true;
                group->w = false;
            }

        }
        //else
           // ui->View->rotate(-30);
}

void MainWindow::on_action_turnright_triggered()//顺时针旋转90度
{
    int cnt=scene->selectedItems().count();
        if (cnt==1)
        {
            QGraphicsItem* item=scene->selectedItems().at(0);
            QPointF center = item->boundingRect().center();
            item->setTransformOriginPoint(center);
            item->setRotation(+90+item->rotation());
            mygroup *group = (mygroup*)item;
            int width = group->width;
           // int height = group->height; if(group->n)   // 左点 上
            if(group->n)
            {
                group->keyright.setY(group->keyright.y()-width/2);
                group->keyright.setX(group->keyright.x()-width/2);
                group->keyleft.setY(group->keyleft.y()+width/2);
                group->keyleft.setX(group->keyleft.x()+width/2);
                group->e = true;
                group->n = false;
            }
            else if(group->s) // 左点下
            {
                group->keyright.setY(group->keyright.y()+width/2);
                group->keyright.setX(group->keyright.x()+width/2);
                group->keyleft.setY(group->keyleft.y()-width/2);
                group->keyleft.setX(group->keyleft.x()-width/2);
                group->w = true;
                group->s = false;
            }
            else if(group->e) // 左点 右
            {
                group->keyright.setY(group->keyright.y()-width/2);
                group->keyright.setX(group->keyright.x()+width/2);
                group->keyleft.setY(group->keyleft.y()+width/2);
                group->keyleft.setX(group->keyleft.x()-width/2);
                group->s = true;
                group->e = false;
            }
            else if(group->w) // 左点 左
            {
                group->keyright.setY(group->keyright.y()+width/2);
                group->keyright.setX(group->keyright.x()-width/2);
                group->keyleft.setY(group->keyleft.y()-width/2);
                group->keyleft.setX(group->keyleft.x()+width/2);
                group->n = true;
                group->w = false;
            }


        }
        //else
            //ui->widget->rotate(+30);
}

void MainWindow::on_action_undo_triggered()
{
    //取消所有变换
        int cnt=scene->selectedItems().count();
        if (cnt==1)
        {
            QGraphicsItem* item=scene->selectedItems().at(0);
    //        item->resetTransform();   //不起作用
            item->setRotation(0);
            item->setScale(1.0);
        }
        //else
            //ui->View->resetTransform();
}

void MainWindow::on_action_word_triggered()
{
       QString str=QInputDialog::getText(this,"输入文字","请输入文字");
        if (str.isEmpty())
            return;

        QGraphicsTextItem   *item=new QGraphicsTextItem(str);

        QFont   font=this->font();
        font.setPointSize(20);
        font.setBold(true);
        item->setFont(font);

        item->setFlags(QGraphicsItem::ItemIsMovable
                       | QGraphicsItem::ItemIsSelectable
                       | QGraphicsItem::ItemIsFocusable);
        item->setPos(-50+(qrand() % 100),-50+(qrand() % 100));

       // QGraphicsItemGroup *group = new QGraphicsItemGroup;
        //group->addToGroup(item);
      //  scene->word_group.push_back(item);
        scene->addItem(item);
        scene->clearSelection();
        item->setSelected(true);
}

void MainWindow::on_action_addlight_triggered()
{
//    light *lightnew = new light;
//    QGraphicsItemGroup *group = lightnew->drawing();
    scene->L = true;
    scene->R = false;
    scene->U = false;
    scene->E = false;
    scene->A = false;
    scene->V = false;
    scene->S = false;
    scene->K = false;
    scene->T = false;
    update();
}

void MainWindow::on_action_addrect_triggered()
{
    scene->R = true;
    scene->U = false;
    scene->E = false;
    scene->A = false;
    scene->V = false;
    scene->S = false;
    scene->K = false;
    scene->T = false;
    scene->L = false;
    update();
}

void MainWindow::on_action_t_triggered()
{
    scene->R = false;
    scene->U = false;
    scene->E = false;
    scene->A = false;
    scene->V = false;
    scene->S = false;
    scene->K = false;
    scene->T = true;
    scene->L = false;
    update();
}

void MainWindow::on_action_k_triggered()
{
    scene->R = false;
    scene->U = false;
    scene->E = false;
    scene->A = false;
    scene->V = false;
    scene->S = false;
    scene->K = true;
    scene->T = false;
    scene->L = false;
    update();
}

void MainWindow::on_action_U_triggered()
{
    scene->R = false;
    scene->U = true;
    scene->E = false;
    scene->A = false;
    scene->V = false;
    scene->S = false;
    scene->K = false;
    scene->T = false;
    scene->L = false;
    update();
}

void MainWindow::on_action_E_triggered()
{
    scene->E = true;
    scene->R = false;
    scene->U = false;
    scene->A = false;
    scene->V = false;
    scene->S = false;
    scene->K = false;
    scene->T = false;
    scene->L = false;
    update();
}

void MainWindow::on_action_A_triggered()
{
    scene->A = true;
    scene->R = false;
    scene->U = false;
    scene->E = false;
    scene->V = false;
    scene->S = false;
    scene->K = false;
    scene->T = false;
    scene->L = false;
    update();
}

void MainWindow::on_action_V_triggered()
{
    scene->R = false;
    scene->U = false;
    scene->E = false;
    scene->A = false;
    scene->V = true;
    scene->S = false;
    scene->K = false;
    scene->T = false;
    scene->L = false;
    update();
}


//void MainWindow::on_action_qt_triggered()
//{
//    QMessageBox::information(this,tr(u8"EDraw")
//                                 ,tr(u8"EDraw是一款轻量的电路图软件\n"
//                                     "\n"
//                                     "版权所有(C) 2020 EDraw\n"
//                                     "本程序为自由软件；您可依据自由软件基金会所发表的GNU通用公共授权条款，对本程序再次发布和/或修改；无论您依据的是本授权的第三版，或（您可选的）任一日后发行的版本。\n"
//                                     "本程序是基于使用目的而加以发布，然而不负任何担保责任；亦无对适售性或特定目的适用性所为的默示性担保。详情请参照GNU通用公共授权。\n"
//                                    ));
//}
void MainWindow::on_action_qt_triggered()
{
    QMessageBox::information(this,tr(u8"EDraw")
                                 ,tr(u8"EDraw是一款轻量的电路图软件\n"
                                     "\n"
                                     "本软件可以实现电路图基本元件的连线，移动，放缩，旋转等功能\n"
                                     "如果您想连线，请先选中任一基本元件，并按下数字1。再选择两个元件。\n"
                                     "请注意，线会从第一个元件的最左边的点连出，并连向第二个元件的最右边的点\n"
                                     "如果您在连线过程中想放弃连线，请按数字0"
                                    ));
}
bool MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this,
                    "Open file as...",
                    "./svg",
                    "All File Type(*.svg)");
    qDebug() << "Open" << fileName;

    QFile* file = new QFile(fileName);
    if(!file->open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("SDI"),tr("Cannot Open File %1:\n%2.").arg(fileName).arg(file->errorString()));
        return false;
    }
    scene->loadScene(file);
    QMessageBox::information(this, "Load Scene", "Loading Scene Successfully!\n");
    file->close();
    return true;
}

bool MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
                    this,
                    "Save file as...",
                    "./svg/test",
                    "All File Type(*.svg)");
    qDebug() << "Save" << fileName;

    QFile* file = new QFile(fileName);

    if (!file->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SDI"),tr("Cannot write file %1:\n%2.").arg(fileName).arg(file->errorString()));
        return false;
    }
    scene->saveScene(file);
    QMessageBox::information(this, "Save Scene", "Save Scene Successfully!\n");
    file->close();
    return true;
}

void MainWindow::on_actionSlide_triggered()
{
    scene->S = true;
    update();
}

void MainWindow::on_actiontool_bar_triggered()
{
    if(flag == 0)
    {
       ui->toolBar->hide();
       flag = 1 ;
    }
    else if(flag == 1)
    {
        ui->toolBar->show();
        flag = 0 ;
    }
}

void MainWindow::on_action_components_triggered()
{
    if(flag2 == 0)
    {
       ui->toolBar_2->hide();
       flag2 = 1 ;
    }
    else if(flag2 == 1)
    {
       ui->toolBar_2->show();
       flag2 = 0 ;
    }
}

void MainWindow::on_action_triggered()
{
    scene->clear();
    scene->ammeter_group.clear();
    scene->capacitance_group.clear();
    scene->light_group.clear();
    scene->power_group.clear();
    scene->rect_group.clear();
    scene->switch_group.clear();
    scene->triangle_group.clear();
    scene->voltmeter_group.clear();
    scene->slide_group.clear();
}

void MainWindow::on_actionnew_triggered()
{
    QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "是否保存该电路图？",
                       QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                       QMessageBox::No);

     if (result==QMessageBox::Yes)
        {
          on_actionSave_triggered();
          scene->clear();
          scene->ammeter_group.clear();
          scene->capacitance_group.clear();
          scene->light_group.clear();
          scene->power_group.clear();
          scene->rect_group.clear();
          scene->switch_group.clear();
          scene->triangle_group.clear();
          scene->voltmeter_group.clear();
          scene->slide_group.clear();
        }
     else if(result==QMessageBox::No)
     {
          scene->clear();
          scene->ammeter_group.clear();
          scene->capacitance_group.clear();
          scene->light_group.clear();
          scene->power_group.clear();
          scene->rect_group.clear();
          scene->switch_group.clear();
          scene->triangle_group.clear();
          scene->voltmeter_group.clear();
          scene->slide_group.clear();
     }
}

void MainWindow::on_action_saveaspicture_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存"),"new.jpg","Imag(*,jpg *.png *.png *bmp)");
    if(fileName.length()>0)
    {
        QPixmap pixmap(size());
        QPainter painter(&pixmap);
        painter.fillRect(QRect(0,0,size().width(),size().height()),Qt::white);
        this->render(&painter);
        pixmap.copy(QRect(0,150,size().width()-100,size().height()-200)).save(fileName);
    } // 保存
}

void MainWindow::on_action_openaspicture_triggered()
{
//    QString picPath = QFileDialog::getOpenFileName(this,tr("打开"),"","Image Files(*.jpg *.png)");
//        if(!picPath.isEmpty())
//        {
//            QPixmap pix2;
//            pix2.load(picPath);+
//            QPainter p(pix);
//            p.drawPixmap(165,0,pix2);
//            update();
//        } // 打开
}
