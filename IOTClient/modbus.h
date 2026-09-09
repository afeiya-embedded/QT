#ifndef MODBUS_H
#define MODBUS_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QComboBox>
#include <QMessageBox>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

    void initUi();          //初始化ui

    bool cmdReadBytes(quint8 readData[],quint8 n);
    bool cmdStatus(quint8 src_cmd[],quint8 n);

private slots:

    void timer_timeout_slot();

    void on_pushButton_reflush_clicked();

    void on_pushButton_open_clicked(bool checked);

    void on_pushButton_led1_clicked(bool checked);

    void on_pushButton_led2_clicked(bool checked);

    void on_pushButton_beep_clicked(bool checked);

    void on_pushButton_relay_clicked(bool checked);

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QSerialPort *serial = nullptr;
    quint8  cmdConBit = 0;      //硬件控制位
    QTimer *timer = nullptr;    //定时器指针 定时2s
    QMutex mutex;               //创建互斥锁
};
#endif // MODBUS_H
