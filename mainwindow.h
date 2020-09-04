#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include "mygraphicsview.h"
#include <QMessageBox>
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QPointF pointScene;
    void paintEvent(QPaintEvent *);
private slots:
    void on_actionBigger_triggered();
    //void on_mouseMovePoint(QPoint point);
    void on_action_smaller_triggered();

    void on_action_turnleft_triggered();

    void on_action_turnright_triggered();

    void on_action_undo_triggered();

    void on_action_word_triggered();

    void on_action_addlight_triggered();

    void on_action_addrect_triggered();

    void on_action_t_triggered();

    void on_action_k_triggered();

    void on_action_U_triggered();

    void on_action_E_triggered();

    void on_action_A_triggered();

    void on_action_V_triggered();

    void on_action_qt_triggered();

    bool on_actionOpen_triggered();

    bool on_actionSave_triggered();

    void on_actionSlide_triggered();

    void on_actiontool_bar_triggered();

    void on_action_components_triggered();
    void closeEvent(QCloseEvent *event);
   // void mouseMoveEvent(QMouseEvent *event);
    void on_action_triggered();

    void on_actionnew_triggered();

    void on_action_saveaspicture_triggered();

    void on_action_openaspicture_triggered();

private:
    Ui::MainWindow *ui;
    Scene *scene;
    Mygraphicsview *view;
    bool flag = 0;
    bool flag2 = 0;
    QPixmap *pix;
};
#endif // MAINWINDOW_H
