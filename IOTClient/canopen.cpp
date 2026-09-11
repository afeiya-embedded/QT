#include "canopen.h"
#include "ui_canopen.h"

CANOpen::CANOpen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CANOpen)
{
    ui->setupUi(this);
    initUi();

    candle_list_handle clist;
    uint8_t num_interfaces;
    candle_handle dev;
    if (candle_list_scan(&clist)) {
        if (candle_list_length(clist, &num_interfaces)) {
            for (uint8_t i=0; i<num_interfaces; i++) {
                if (candle_dev_get(clist, i, &dev)) {
                    CanDevice device;
                    device.id = i;
                    device.handle = dev;
                    device.name = "candle" + QString::number(device.id & 0xFF);
                    device.desc = QString::fromStdWString(candle_dev_get_path(dev));
                    ui->comboBox_can->addItem(device.name);
                    candevices.append(device);
                }
            }
        }
        candle_list_free(clist);
    }

    //设置信号处理函数
    connect(this, &CANOpen::receiveeCanData, this, &CANOpen::receiveeCanData_slot);

    //定时器
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, &CANOpen::timer_timeout_slot);
}

CANOpen::~CANOpen()
{
    delete ui;
}

void CANOpen::initUi()
{
    //设置
    ui->label->setStyleSheet("color:white;");

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
}

void CANOpen::on_pushButton_reflush_clicked()
{
    ui->comboBox_can->clear();
    candle_list_handle clist;
    uint8_t num_interfaces;
    candle_handle dev;
    if (candle_list_scan(&clist)) {
        if (candle_list_length(clist, &num_interfaces)) {
            for (uint8_t i=0; i<num_interfaces; i++) {
                if (candle_dev_get(clist, i, &dev)) {
                    CanDevice device;
                    device.id = i;
                    device.handle = dev;
                    device.name = "candle" + QString::number(device.id & 0xFF);
                    device.desc = QString::fromStdWString(candle_dev_get_path(dev));
                    ui->comboBox_can->addItem(device.name);
                    candevices.append(device);
                }
            }
        }
        candle_list_free(clist);
    }
}

//线程函数
void CANOpen::readMessage()
{
    qDebug() << "readMessage";

    while(ui->pushButton_open->isChecked())
    {
        //设备打开 一直循环获取信息

        CanDevice device = candevices[ui->comboBox_can->currentIndex()];
        candle_frame_t frame;
        if(candle_frame_read(device.handle,&frame,1000))//读取设备数据
        {
            auto frame_type = candle_frame_type(&frame);
            qDebug() << "frame_type=" << frame_type;
            if(frame_type == CANDLE_FRAMETYPE_RECEIVE)//成功接收1帧数据
            {
                quint32 canid = candle_frame_id(&frame);//帧ID号
                quint8 candlc = candle_frame_dlc(&frame);//数据包长度
                quint8 *data = candle_frame_data(&frame);//can的帧数据
                QByteArray byteArr((char *)data,candlc);
                // qDebug() << "byteArr:" << byteArr;
                // qDebug("canid:%#x",canid);
                // qDebug("candlc:%#x",candlc);

                //发送信号给主程序数据来了
                emit receiveeCanData(canid, candlc, byteArr);
                //qDebug() << "receiveeCanData emit";
            }
        }

        QThread::msleep(100);
    }
}

void CANOpen::receiveeCanData_slot(quint32 id, quint8 dlc, QByteArray recvdata)
{
    //qDebug() << "receiveeCanData_slot";

    quint8* recvData =  (quint8 *)recvdata.data();//把byteArray转成quint8*类型数据
    // for (int i = 0; i < dlc; ++i) {
    //     qDebug("->0x%x ", recvData[i]);
    // }
    if((id == 0x581) && (dlc == 8))
    {
        if( (recvData[0] == 0x60) && (recvData[1] == 0x00) &&
            (recvData[2] == 0x20) && (recvData[3] == 0x01) )
        {
            //led1
            if(ui->pushButton_led1->isChecked())
            {
                ui->pushButton_led1->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led1on.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                ui->pushButton_led1->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led1off.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            //led2
            if(ui->pushButton_led2->isChecked())
            {
                ui->pushButton_led2->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led2on.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                ui->pushButton_led2->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led2off.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            //beep
            if(ui->pushButton_beep->isChecked())
            {
                ui->pushButton_beep->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/beepon.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                ui->pushButton_beep->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/beepoff.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            //relay
            if(ui->pushButton_relay->isChecked())
            {
                ui->pushButton_relay->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/relayon.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                ui->pushButton_relay->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/relayoff.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00) &&
                 (recvData[2] == 0x20) && (recvData[3] == 0x02) )//温度
        {
            quint16 temp = (recvData[5] << 8) | recvData[4];
            ui->pushButton_temp->setText(QString::asprintf("%.1f",temp/100.0) + "℃");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00) &&
                 (recvData[2] == 0x20) && (recvData[3] == 0x03) )//湿度
        {
            quint16 hum = (recvData[5] << 8) | recvData[4];
            ui->pushButton_hum->setText(QString::asprintf("%.1f",hum/100.0) + "%");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00) &&
                 (recvData[2] == 0x20) && (recvData[3] == 0x04) )//系统电压
        {
            quint16 vol = (recvData[5] << 8) | recvData[4];
            ui->pushButton_vol->setText(QString::asprintf("%.2f",vol/100.0) + "V");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00) &&
                 (recvData[2] == 0x20) && (recvData[3] == 0x05) )//系统电流
        {
            quint16 cur = (recvData[5] << 8) | recvData[4];
            ui->pushButton_cur->setText(QString::asprintf("%.0f",cur/1.0) + "mA");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00) &&
                 (recvData[2] == 0x20) && (recvData[3] == 0x06) )//功率
        {
            quint16 pw = (recvData[5] << 8) | recvData[4];
            ui->pushButton_pw->setText(QString::asprintf("%.2f",pw/1000.0) + "W");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00) &&
                 (recvData[2] == 0x20) && (recvData[3] == 0x07) )//电位器
        {
            quint16 vr = (recvData[5] << 8) | recvData[4];
            ui->pushButton_vr->setText(QString::asprintf("%.2f",vr/100.0) + "V");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00) &&
                 (recvData[2] == 0x20) && (recvData[3] == 0x08) )//cpu
        {
            quint16 cpu = (recvData[5] << 8) | recvData[4];
            ui->pushButton_cpu->setText(QString::asprintf("%.1f",cpu/100.0) + "℃");
        }
    }
}

void CANOpen::on_pushButton_open_clicked(bool checked)
{
    //qDebug() << "checked=" << checked;

    CanDevice device = candevices[ui->comboBox_can->currentIndex()];//当前设备candle0

    if(checked) // 为真 打开设备
    {
        if (!candle_dev_open(device.handle)) {
            qDebug()<<"open failed";
            return;
        }

        // 读取can的属性信息
        candle_capability_t caps;//设备信息
        if (!candle_channel_get_capabilities(device.handle, 0, &caps)) {
            //qDebug()<<"candle_channel_get_capabilities failed";
            return;
        }
        else
        {
            qDebug()<<"scan attribute:" << caps.fclk_can << caps.brp_min << caps.brp_max << caps.brp_inc << caps.feature;
        }

        // 500000, 875 ， 设置波特率 500K
        candle_bittiming_t timing;//波特率
        //默认值
        timing.brp = 6;
        timing.phase_seg1 = 12;
        timing.phase_seg2 = 2;
        timing.sjw = 1;
        timing.prop_seg = 1;
        if(!candle_channel_set_timing(device.handle, 0, &timing))
        {
            qDebug()<<"candle_channel_set_timing failed";
            return;
        }

        //获取设备时间戳
        uint32_t t_dev;
        candle_dev_get_timestamp_us(device.handle, &t_dev);
        //开始捕捉CAN总线通道0的数据
        uint32_t flags = 0;
        // flags |= CANDLE_MODE_LISTEN_ONLY;
        // flags |= CANDLE_MODE_ONE_SHOT;
        // flags |= CANDLE_MODE_TRIPLE_SAMPLE;
        if(candle_channel_start(device.handle, 0, flags) )
        {
            qDebug() <<device.name << "candle_channel_start scuessed" ;
        }
        else
        {
            qDebug() <<device.name << "candle_channel_start failed" ;
        }

        // 设置信号处理函数 SigReceiveCanData
        // 开启1个线程 , 保存函数
        future = QtConcurrent::run(this,&CANOpen::readMessage);

        ui->pushButton_open->setText(tr("关闭设备"));

        // 启动定时器
        if(timer != nullptr)
        {
            timer->start(2000);
        }
    }
    else // 为假 关闭设备
    {
        candle_dev_close(device.handle);//关闭设备
        future.cancel(); // 取消线程， 关闭线程
        future.waitForFinished();//等待线程结束
        if (future.isCanceled())
        {
            qDebug() << "The task has been successfully canceled.";
        }
        else
        {
            qDebug() << "The task was not canceled or has not finished yet.";
        }

        qDebug()<<"stop :" << candle_channel_stop(device.handle, 0);
        qDebug()<<"close :" <<candle_dev_close(device.handle);

        ui->pushButton_open->setText(tr("打开设备"));

        //关闭定时器
        if(timer != nullptr)
        {
            timer->stop();
        }

    }
}

void CANOpen::on_pushButton_led1_clicked(bool checked)
{
    CanDevice device = candevices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked)//led1 on
    {
        cmdConBit = cmdConBit | (1<<0);
    }
    else//led1 off
    {
        cmdConBit = cmdConBit & (~(1<<0));
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 0x8;
    frame.can_id = 0x601;
    qDebug() << "candle_frame_send" << candle_frame_send(device.handle,0,&frame);
}

void CANOpen::on_pushButton_led2_clicked(bool checked)
{
    CanDevice device = candevices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked)//led2 on
    {
        cmdConBit = cmdConBit | (1<<1);
    }
    else//led2 off
    {
        cmdConBit = cmdConBit & (~(1<<1));
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 0x8;
    frame.can_id = 0x601;
    qDebug() << "candle_frame_send" << candle_frame_send(device.handle,0,&frame);
}


void CANOpen::on_pushButton_beep_clicked(bool checked)
{
    CanDevice device = candevices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked)//beep on
    {
        cmdConBit = cmdConBit | (1<<2);
    }
    else//beep off
    {
        cmdConBit = cmdConBit & (~(1<<2));
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 0x8;
    frame.can_id = 0x601;
    qDebug() << "candle_frame_send" << candle_frame_send(device.handle,0,&frame);
}

void CANOpen::on_pushButton_relay_clicked(bool checked)
{
    CanDevice device = candevices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked)//relay on
    {
        cmdConBit = cmdConBit | (1<<3);
    }
    else//relay off
    {
        cmdConBit = cmdConBit & (~(1<<3));
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 0x8;
    frame.can_id = 0x601;
    qDebug() << "candle_frame_send" << candle_frame_send(device.handle,0,&frame);
}

void CANOpen::timer_timeout_slot()
{
    //qDebug() << "timer_timeout_slot";

    CanDevice device = candevices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;

    frame.data[0] = 0x4b;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x02;
    frame.data[4] = 0x00;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 0x8;
    frame.can_id = 0x601;

    //温度
    candle_frame_send(device.handle,0,&frame);

    //湿度
    frame.data[3] = 0x03;
    candle_frame_send(device.handle,0,&frame);

    //系统电压
    frame.data[3] = 0x04;
    candle_frame_send(device.handle,0,&frame);

    //系统电流
    frame.data[3] = 0x05;
    candle_frame_send(device.handle,0,&frame);

    //功率
    frame.data[3] = 0x06;
    candle_frame_send(device.handle,0,&frame);

    //电位器
    frame.data[3] = 0x07;
    candle_frame_send(device.handle,0,&frame);

    //cpu
    frame.data[3] = 0x08;
    candle_frame_send(device.handle,0,&frame);
}