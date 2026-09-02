#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPen>
#include <QSettings>

#include "polygon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    // 这个函数是虚函数, 子类重新实现父类的方法
    // 实现绘画事件 paintEvent
    // 在窗口被显示的时候调用一次 , 窗口发生改变时都会被调用
    // 手动使用update 函数时 也会被调用
    void paintEvent(QPaintEvent *event);

    // 这几个函数是虚函数, 这里时重新实现QWidget的函数, 子类覆盖父类
    void mousePressEvent(QMouseEvent *event); // 鼠标按压事件
    void mouseReleaseEvent(QMouseEvent *event); // 鼠标释放事件
    void mouseMoveEvent(QMouseEvent *event); // 鼠标移动事件

private slots:
    void on_action_load_triggered();

    void on_action_line_triggered();

    void on_action_polygon_triggered();

    void add_newpolygon_slot();


    void on_action_clear_triggered();

private:
    Ui::MainWindow *ui;
    QString fileName;               //保存背景
    bool drawLineFlag = false;      //画线标志位
    bool drawPolygonFlag = false;   //多边形标志位
    QLine line;                     //线条
    quint32 linePointIndex = 0;     //线条端点
    quint32 polygonPointIndex = 0;   //多边形端点
    polygon *polygonP = nullptr;    //多边形指针
    QPolygon ply;                   //多边形对象

    QSettings set;                  //系统配置对象
};
#endif // MAINWINDOW_H
