#ifndef CANOPEN_H
#define CANOPEN_H

#include <QWidget>
#include <QtMqtt/QMqttClient>
#include <QtConcurrent>
#include <QTimer>

#include "api/candle.h"

namespace Ui {
class CANOpen;
}

struct CanDevice
{
    candle_handle handle;
    uint32_t id;
    QString name;
    QString desc; // 驱动描述
};

class CANOpen : public QWidget
{
    Q_OBJECT


public:
    explicit CANOpen(QWidget *parent = nullptr);
    ~CANOpen();

    void initUi();          //初始化ui
    void readMessage();

signals:
    void receiveeCanData(quint32 id, quint8 dlc, QByteArray data);

private slots:
    void receiveeCanData_slot(quint32 id, quint8 dlc, QByteArray data);

    void on_pushButton_open_clicked(bool checked);

    void on_pushButton_reflush_clicked();

    void on_pushButton_led1_clicked(bool checked);

    void on_pushButton_led2_clicked(bool checked);

    void on_pushButton_beep_clicked(bool checked);

    void on_pushButton_relay_clicked(bool checked);

    void timer_timeout_slot();

private:
    Ui::CANOpen *ui;
    QList<CanDevice> candevices;//定义candevices 设备列表
    QFuture<void> future;       //模板类
    quint8  cmdConBit = 0;      //硬件控制位
    QTimer *timer;


};

#endif // CANOPEN_H
