#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QStandardItemModel>
#include <QTranslator>


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

private slots:
    void on_pushButton_start_clicked(bool checked);

    void on_pushButton_reset_clicked();

    void on_action_language_triggered();

private:
    void timeout_slot();

private:
    Ui::MainWindow *ui;
    qint32 min = 0, sec = 0, msec = 0;  //定义时间单位
    QTimer *timer = nullptr;
    QStandardItemModel * model ; // QStandardItemModel 这是一个标准的model/view的框架
    qint32 lineCount = 0;
    bool language = true;       //true:Enlish false:中文
};
#endif // MAINWINDOW_H
