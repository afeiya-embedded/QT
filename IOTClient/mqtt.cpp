#include "mqtt.h"
#include "ui_mqtt.h"

MQTT::MQTT(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MQTT),set("config.ini",QSettings::IniFormat)
{
    ui->setupUi(this);
    initUi();
}

MQTT::~MQTT()
{
    delete ui;
}

void MQTT::initUi()
{
    //设置
    ui->label_server->setStyleSheet("color:white;");
    ui->label_upload->setStyleSheet("color:white;");
    ui->label_download->setStyleSheet("color:white;");

    ui->pushButton_led1->setStyleSheet("QPushButton{"
                                       "border-image: url(:/images/led1off.png);"
                                       "border: none;"
                                       "}"
                                       );

    ui->pushButton_led2->setStyleSheet("QPushButton{"
                                       "border-image: url(:/images/led2off.png);"
                                       "border: none;"
                                       "}"
                                       );


    ui->pushButton_beep->setStyleSheet("QPushButton{"
                                       "border-image: url(:/images/beepoff.png);"
                                       "border: none;"
                                       "}"
                                       );


    ui->pushButton_relay->setStyleSheet("QPushButton{"
                                        "border-image: url(:/images/relayoff.png);"
                                        "border: none;"
                                        "}"
                                        );


    ui->pushButton_hum->setStyleSheet("QPushButton{"
                                      "border-image: url(:/images/hum.png);"
                                      "color:white;"
                                      "border: none;"
                                      "padding-right: 10px;"
                                      "padding-top: 26px;"
                                      "padding-bottom: 0px;"
                                      "text-align: bottom right;"
                                      "}"
                                      );
    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei"));
    font.setPointSize(16);
    font.setBold(true);
    ui->pushButton_hum->setFont(font);

    ui->pushButton_temp->setStyleSheet("QPushButton{"
                                       "border-image: url(:/images/temp.png);"
                                       "color:white;"
                                       "border: none;"
                                       "padding-right: 10px;"
                                       "padding-top: 26px;"
                                       "padding-bottom: 0px;"
                                       "text-align: bottom right;"
                                       "}"
                                       );
    ui->pushButton_temp->setFont(font);



    ui->pushButton_cpu->setStyleSheet("QPushButton{"
                                      "border-image: url(:/images/cpu.png);"
                                      "color:white;"
                                      "border: none;"
                                      "padding-right: 10px;"
                                      "padding-top: 26px;"
                                      "padding-bottom: 0px;"
                                      "text-align: bottom right;"
                                      "}"
                                      );
    ui->pushButton_cpu->setFont(font);


    ui->pushButton_cur->setStyleSheet("QPushButton{"
                                      "border-image: url(:/images/cur.png);"
                                      "color:white;"
                                      "border: none;"
                                      "padding-right: 10px;"
                                      "padding-top: 26px;"
                                      "padding-bottom: 0px;"
                                      "text-align: bottom right;"
                                      "}"
                                      );
    ui->pushButton_cur->setFont(font);


    ui->pushButton_vol->setStyleSheet("QPushButton{"
                                      "border-image: url(:/images/vol.png);"
                                      "color:white;"
                                      "border: none;"
                                      "padding-right: 10px;"
                                      "padding-top: 26px;"
                                      "padding-bottom: 0px;"
                                      "text-align: bottom right;"
                                      "}"
                                      );
    ui->pushButton_vol->setFont(font);

    ui->pushButton_vr->setStyleSheet("QPushButton{"
                                     "border-image: url(:/images/vr.png);"
                                     "color:white;"
                                     "border: none;"
                                     "padding-right: 10px;"
                                     "padding-top: 26px;"
                                     "padding-bottom: 0px;"
                                     "text-align: bottom right;"
                                     "}"
                                     );
    ui->pushButton_vr->setFont(font);


    ui->pushButton_pw->setStyleSheet("QPushButton{"
                                     "border-image: url(:/images/pw.png);"
                                     "color:white;"
                                     "border: none;"
                                     "padding-right: 10px;"
                                     "padding-top: 26px;"
                                     "padding-bottom: 0px;"
                                     "text-align: bottom right;"
                                     "}"
                                     );
    ui->pushButton_pw->setFont(font);

    ui->pushButton_open->setStyleSheet("QPushButton{border-radius: 5px; background-color: white;}"  //正常状态
                                       "QPushButton:pressed{color:white; background-color: #5354cb}"             //按压状态
                                       "QPushButton:checked{color:white; background-color: #5354cb}"             //选中状态
                                     "}"
                                     );
    ui->pushButton_pw->setFont(font);


    //如果MQTT有server 这个key , 说明我们配置文件中已经保存了server , 此时就需要我们加载即可
    if(set.contains("MQTT/server")) // 可以在config.ini 进行搜索 , 找到和没找到两种
    {
        QString mqttserver = set.value("MQTT/server").toString();
        QString upload = set.value("MQTT/UpLoad").toString();
        QString dowmload = set.value("MQTT/DownLoad").toString();

        ui->comboBox_server->addItem(mqttserver);
        ui->comboBox_upload->addItem(upload);
        ui->comboBox_download->addItem(dowmload);
    }
    else // 如果没有就创建 这些值
    {
        QString mqttserver = "broker.emqx.io";
        QString upload = "STM32/UpLoad/8708603349498271066CFF52";
        QString dowmload = "STM32/DownLoad/8708603349498271066CFF52";

        set.setValue("MQTT/server",mqttserver);
        set.setValue("MQTT/UpLoad",upload);
        set.setValue("MQTT/DownLoad",dowmload);

        ui->comboBox_server->addItem(mqttserver);
        ui->comboBox_upload->addItem(upload);
        ui->comboBox_download->addItem(dowmload);
    }
}

void MQTT::mqtt_stateChanged_slot(QMqttClient::ClientState state)
{
    //qDebug() << "mqtt_stateChanged_slot=" << state;
    if(state == QMqttClient::Connecting)
    {
        qDebug() << "mqttclient connecting mqttserver...";
        //不可操作
        ui->comboBox_server->setEnabled(false);
        ui->comboBox_download->setEnabled(false);
        ui->comboBox_upload->setEnabled(false);
    }
    else if(state == QMqttClient::Connected)
    {
        qDebug() << "mqttclient connected mqttserver";
        ui->pushButton_open->setText(tr("断开连接"));

        //订阅主题
        QMqttSubscription *sub =  mqttclient->subscribe(ui->comboBox_upload->currentText());
        if(sub == nullptr)
        {
            qDebug() << "mqttclient subscribe failed";
        }
        else
        {
            qDebug() << "mqttclient subscribe ok";
        }
    }
    else if(state == QMqttClient::Disconnected)
    {
        qDebug() << "mqttclient disconnected mqttserver";
        ui->pushButton_open->setText(tr("连接服务器"));
        //可操作
        ui->comboBox_server->setEnabled(true);
        ui->comboBox_download->setEnabled(true);
        ui->comboBox_upload->setEnabled(true);

        //取消订阅
        mqttclient->unsubscribe(ui->comboBox_upload->currentText());

        if(mqttclient != nullptr)
        {
            mqttclient->cleanSession();
            mqttclient->deleteLater();
            mqttclient = nullptr;
        }
    }
}

void MQTT::mqtt_messageReceived_slot(const QByteArray &message, const QMqttTopicName &topic)
{


    if(topic == ui->comboBox_upload->currentText())//主题匹配
    {
        // qDebug() << "  topic=" << topic;
        // qDebug() << "message=" << message;

        //将message转成json字符串
        QJsonDocument jsonstr = QJsonDocument::fromJson(message);
        if(!jsonstr.isNull())//判非空
        {
            //进行数据解析
            QJsonObject jsonObject =  jsonstr.object();
            QJsonValue jsonTP =  jsonObject.value("TP");
            QJsonValue jsonRH =  jsonObject.value("RH");
            QJsonValue jsonVO =  jsonObject.value("VO");
            QJsonValue jsonCU =  jsonObject.value("CU");
            QJsonValue jsonPW =  jsonObject.value("PW");
            QJsonValue jsonVR =  jsonObject.value("VR");
            QJsonValue jsonCPU =  jsonObject.value("CPU");

            if(!jsonTP.isNull())
            {
                ui->pushButton_temp->setText(QString::asprintf("%.1f",jsonTP.toInt()/100.0) + "℃");
            }
            if(!jsonRH.isNull())
            {
                ui->pushButton_hum->setText(QString::asprintf("%.1f",jsonRH.toInt()/100.0) + "%");
            }
            if(!jsonVO.isNull())
            {
                ui->pushButton_vol->setText(QString::asprintf("%.2f",jsonVO.toInt()/100.0) + "V");
            }
            if(!jsonCU.isNull())
            {
                ui->pushButton_cur->setText(QString::asprintf("%.0f",jsonCU.toInt()/1.0) + "mA");
            }
            if(!jsonPW.isNull())
            {
                ui->pushButton_pw->setText(QString::asprintf("%.2f",jsonPW.toInt()/1000.0) + "W");
            }
            if(!jsonVR.isNull())
            {
                ui->pushButton_vr->setText(QString::asprintf("%.2f",jsonVR.toInt()/100.0) + "V");
            }
            if(!jsonCPU.isNull())
            {
                ui->pushButton_cpu->setText(QString::asprintf("%.1f",jsonCPU.toInt()/100.0) + "℃");
            }
        }
    }

}


void MQTT::on_pushButton_open_clicked(bool checked)
{
    if(checked)//连接服务器
    {
        mqttclient = new QMqttClient(this);
        mqttclient->setHostname(ui->comboBox_server->currentText());//设置服务器 broker.emqx.io
        mqttclient->setPort(1883);//设置端口号

        //设置心跳包
        mqttclient->setKeepAlive(60);//设置60s自动连接

        //设置信号处理函数
        connect(mqttclient, &QMqttClient::stateChanged, this, &MQTT::mqtt_stateChanged_slot);
        connect(mqttclient, &QMqttClient::messageReceived, this, &MQTT::mqtt_messageReceived_slot);

        //连接服务器
        mqttclient->connectToHost();

        qDebug() << "自动生成的客户端ID=" << mqttclient->clientId();
    }
    else//断开服务器
    {
        if(mqttclient != nullptr)
        {
            mqttclient->disconnectFromHost();//断开连接
        }
    }
}


void MQTT::on_pushButton_led1_clicked(bool checked)
{
    QJsonObject cmd_json;
    //{LED1:true}  led1 on
    //{LED1:false} led1 off
    if(checked)//led1 on
    {
        cmd_json.insert("LED1",true);
        ui->pushButton_led1->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/led1on.png);"
                                           "border: none;"
                                           "}"
                                           );
    }
    else//led1 off
    {
        cmd_json.insert("LED1",false);
        ui->pushButton_led1->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/led1off.png);"
                                           "border: none;"
                                           "}"
                                           );
    }

    QJsonDocument doc;//json字符串
    doc.setObject(cmd_json);//初始化字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//把json字符串转成bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(), cmdArray);//发送数据
    }
}


void MQTT::on_pushButton_led2_clicked(bool checked)
{
    QJsonObject cmd_json;

    if(checked)//led2 on
    {
        cmd_json.insert("LED2",true);
        ui->pushButton_led2->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/led2on.png);"
                                           "border: none;"
                                           "}"
                                           );
    }
    else//led2 off
    {
        cmd_json.insert("LED2",false);
        ui->pushButton_led2->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/led2off.png);"
                                           "border: none;"
                                           "}"
                                           );
    }

    QJsonDocument doc;//json字符串
    doc.setObject(cmd_json);//初始化字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//把json字符串转成bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(), cmdArray);//发送数据
    }
}


void MQTT::on_pushButton_beep_clicked(bool checked)
{
    QJsonObject cmd_json;

    if(checked)//beep on
    {
        cmd_json.insert("BEEP",true);
        ui->pushButton_beep->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/beepon.png);"
                                           "border: none;"
                                           "}"
                                           );
    }
    else//beep off
    {
        cmd_json.insert("BEEP",false);
        ui->pushButton_beep->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/beepoff.png);"
                                           "border: none;"
                                           "}"
                                           );
    }

    QJsonDocument doc;//json字符串
    doc.setObject(cmd_json);//初始化字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//把json字符串转成bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(), cmdArray);//发送数据
    }
}


void MQTT::on_pushButton_relay_clicked(bool checked)
{
    QJsonObject cmd_json;

    if(checked)//relay on
    {
        cmd_json.insert("RELAY",true);
        ui->pushButton_relay->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/relayon.png);"
                                           "border: none;"
                                           "}"
                                           );
    }
    else//relay off
    {
        cmd_json.insert("RELAY",false);
        ui->pushButton_relay->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/relayoff.png);"
                                           "border: none;"
                                           "}"
                                           );
    }

    QJsonDocument doc;//json字符串
    doc.setObject(cmd_json);//初始化字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//把json字符串转成bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(), cmdArray);//发送数据
    }
}


void MQTT::on_comboBox_upload_currentTextChanged(const QString &arg1)
{
    set.setValue("MQTT/UpLoad",ui->comboBox_upload->currentText());
}


void MQTT::on_comboBox_download_currentTextChanged(const QString &arg1)
{
    set.setValue("MQTT/DownLoad",ui->comboBox_download->currentText());
}


void MQTT::on_comboBox_server_currentTextChanged(const QString &arg1)
{
    set.setValue("MQTT/server",ui->comboBox_server->currentText());
}

