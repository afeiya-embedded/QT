#ifndef MQTT_H
#define MQTT_H

#include <QWidget>
#include <QtMqtt/QMqttClient>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class MQTT;
}

class MQTT : public QWidget
{
    Q_OBJECT

public:
    explicit MQTT(QWidget *parent = nullptr);
    ~MQTT();

    void initUi();          //初始化ui

private slots:
    void mqtt_messageReceived_slot(const QByteArray &message, const QMqttTopicName &topic);

    void mqtt_stateChanged_slot(QMqttClient::ClientState state);

    void on_pushButton_open_clicked(bool checked);

    void on_pushButton_led1_clicked(bool checked);

    void on_pushButton_led2_clicked(bool checked);

    void on_pushButton_beep_clicked(bool checked);

    void on_pushButton_relay_clicked(bool checked);

private:
    Ui::MQTT *ui;
    QMqttClient *mqttclient = nullptr;//mqtt客户端
};

#endif // MQTT_H
