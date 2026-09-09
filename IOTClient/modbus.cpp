#include "modbus.h"
#include "ui_modbus.h"

#include "canopen.h"
#include "mqtt.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initUi();

    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts() ;
    foreach (QSerialPortInfo port, serialPorts) {
        qDebug() << "串口名：" << port.portName() ; // 串口名称
        qDebug() << "串口描述: " << port.description() ; // 串口描述
        ui->comboBox->addItem(port.portName()+" #"+port.description(),QVariant(port.portName()));
    }

    //设置定时器 2s更新
    timer = new QTimer(this);
    //设置信号
    connect(timer, &QTimer::timeout, this, &Widget::timer_timeout_slot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_open_clicked(bool checked)
{
    if(checked)
    {
        qDebug() << "portName=" << ui->comboBox->currentData().toString();
        serial = new QSerialPort(this);
        serial->setPortName(ui->comboBox->currentData().toString());

        //打开串口
        if(serial->open(QIODevice::ReadWrite))
        {
            ui->pushButton_open->setText(tr("关闭串口"));
            ui->comboBox->setEnabled(false);
            serial->setBaudRate(QSerialPort::Baud115200);
            serial->setParity(QSerialPort::NoParity);
            serial->setDataBits(QSerialPort::Data8);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setReadBufferSize(1);//接收缓存区1个字节 收到1个字节就发送信号 readReady信号

            //启动定时器
            if(timer != nullptr)
            {
                timer->start(2000);//2s更新
            }
        }
        else
        {
            if(serial != nullptr)
            {
                serial->close();
                serial->deleteLater();
                serial = nullptr;
            }
            ui->pushButton_open->setText(tr("打开串口"));
            ui->comboBox->setEnabled(true);
            ui->pushButton_open->setChecked(false);//抬起按钮
            QMessageBox::warning(this,tr("打开串口失败"),tr("串口被其他进程占用，关闭其他进程再打开"));
            return;
        }
    }
    else
    {
        if(serial != nullptr)
        {
            serial->close();
            serial->deleteLater();
            serial = nullptr;
        }
        ui->pushButton_open->setText(tr("打开串口"));
        ui->comboBox->setEnabled(true);
        //关闭定时器
        if(timer != nullptr)
        {
            timer->stop();
        }
    }
}

void Widget::on_pushButton_reflush_clicked()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts() ;
    foreach (QSerialPortInfo port, serialPorts) {
        qDebug() << "串口名: " << port.portName() ; // 串口名称
        qDebug() << "串口描述: " << port.description() ; // 串口描述
        ui->comboBox->addItem(port.portName()+" #"+port.description(),QVariant(port.portName()));
    }
}


//数组首地址、 数组长度-2（不包含校验玛）
unsigned int make_crc(unsigned char *puchMsg,unsigned int usDataLen)
{
    unsigned char i;
    unsigned int crc=0XFFFF;
    while(usDataLen--!=0)
    {
        crc=crc^(*puchMsg);
        for(i=0;i<8;i++){if((crc&0x0001)==1){crc=crc>>1;crc^=0XA001;}else{crc=crc>>1;}}
        puchMsg++;
    }
    return(crc);
}
// 成功读取返回 ： true
// 失败读取返回 ： false
bool Widget::cmdReadBytes(quint8 readData[],quint8 n)
{
    // 在 115200 的波特率下发送 100 字节需要约 6.944 毫秒。
    if (!serial->waitForReadyRead(3000)) return false;
    QByteArray data = serial->readAll();
    while (serial->waitForReadyRead(10))
        data += serial->readAll();
    for(qint32 i=0;i<data.size();i++)
    {
        readData[i] = quint8(data.at(i)) ;// 数据入队
        //qDebug("%#x",quint8(data.at(i))) ;
    }
    quint16 recv_crc = (readData[n-1] << 8) | readData[n-2] ;
    quint16 calc_crc = make_crc(readData,n-2);// 计算出的crc
    // qDebug("recv_crc = %#x",recv_crc) ;
    // qDebug("calc_crc = %#x",calc_crc) ;
    if( recv_crc == calc_crc )
    {
        return true;
    }
    else
    {
        static qint32 count =0 ;
        qDebug("crc校验失败次数:%d",++count) ;
        return false;
    }
}

// 返回真 ： 表示命令发送成功
// 返回假 ： 表示命令发送失败
bool Widget::cmdStatus(quint8 src_cmd[],quint8 n)
{
    quint8 dst_cmd[128];
    // 在 115200 的波特率下发送 100 字节需要约 6.944 毫秒。
    if (!serial->waitForReadyRead(1000)) return false;
    QByteArray data = serial->readAll();
    while (serial->waitForReadyRead(10))
        data += serial->readAll();
    for(qint32 i=0;i<data.size();i++)
    {
        dst_cmd[i] = quint8(data.at(i)) ;// 数据入队
        qDebug() << "->:0x%02x" << quint8(data.at(i));
    }
    if( memcmp(src_cmd,dst_cmd,n) == 0 )
    {
        return true;
    }
    else
    {
        qDebug() << "cmdStatus memcpy failed";
        return false;
    }
}


void Widget::on_pushButton_led1_clicked(bool checked)
{
    QMutexLocker locker(&mutex);//上锁 函数结束自动释放锁

    if(checked)     //ledon
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<0);//led1on
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "led11 on";
                ui->pushButton_led1->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led1on.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "led11 open failed";
                ui->pushButton_led1->setChecked(false);//按键抬起
                return;
            }
        }
    }
    else            //ledoff
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<0));//led1off
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "led12 on";
                ui->pushButton_led1->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led1off.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "led12 open failed";
                ui->pushButton_led1->setChecked(false);//按键抬起
                return;
            }
        }
    }
}


void Widget::on_pushButton_led2_clicked(bool checked)
{
    QMutexLocker locker(&mutex);//上锁 函数结束自动释放锁

    if(checked)     //ledon
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<1);//led1on
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "led21 on";
                ui->pushButton_led2->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led2on.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "led21 open failed";
                ui->pushButton_led2->setChecked(false);//按键抬起
                return;
            }
        }
    }
    else            //ledoff
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<1));//led1off
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "led22 on";
                ui->pushButton_led2->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/led2off.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "led22 open failed";
                ui->pushButton_led2->setChecked(false);//按键抬起
                return;
            }
        }
    }
}


void Widget::on_pushButton_beep_clicked(bool checked)
{
    QMutexLocker locker(&mutex);//上锁 函数结束自动释放锁

    if(checked)     //beepon
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<2);//beepon
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "beep on";
                ui->pushButton_beep->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/beepon.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "beep open failed";
                ui->pushButton_beep->setChecked(false);//按键抬起
                return;
            }
        }
    }
    else            //ledoff
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<2));//beepoff
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "beep on";
                ui->pushButton_beep->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/beepoff.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "beep open failed";
                ui->pushButton_beep->setChecked(false);//按键抬起
                return;
            }
        }
    }
}


void Widget::on_pushButton_relay_clicked(bool checked)
{
    QMutexLocker locker(&mutex);//上锁 函数结束自动释放锁

    if(checked)     //relay
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<3);//relayon
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "relay on";
                ui->pushButton_relay->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/relayon.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "relay open failed";
                ui->pushButton_relay->setChecked(false);//按键抬起
                return;
            }
        }
    }
    else            //relayoff
    {
        cmdConBit = 0;
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<3));//relayoff
        cmd[5] = cmdConBit;
        quint16 crc16 = make_crc(cmd, 6);
        cmd[6] = crc16&0xff;//得到低8位
        cmd[7] = crc16>>8;//得到高8位

        if(serial != nullptr)
        {
            serial->write((char*)cmd, 8);
            if(cmdStatus(cmd, 8))//命令发送成功
            {
                qDebug() << "relay on";
                ui->pushButton_relay->setStyleSheet("QPushButton{"
                                                   "border-image: url(:/images/relayoff.png);"
                                                   "border: none;"
                                                   "}"
                                                   );
            }
            else
            {
                qDebug() << "relay open failed";
                ui->pushButton_relay->setChecked(false);//按键抬起
                return;
            }
        }
    }
}

void Widget::timer_timeout_slot()
{
    QMutexLocker locker(&mutex);//上锁 函数结束自动释放锁

    qDebug() << "timer_timeout_slot";

    quint8 cmd[] = {0x01, 0x03, 0x00, 0x01, 0x00, 0x07, 0x00, 0x00};

    quint16 crc16 = make_crc(cmd, 6);
    cmd[6] = crc16&0xff;//得到低8位
    cmd[7] = crc16>>8;//得到高8位
    quint8 readData[128]={0};
    if(serial != nullptr)
    {
        serial->write((char*)cmd, 8);
        if(cmdReadBytes(readData, 19))//读到数据 校验成功
        {
            qDebug() << "data recv ok";

            quint16 temp = ((readData[3] << 8) | readData[4]);//温度
            quint16 hum = ((readData[5] << 8) | readData[6]);//湿度
            quint16 vol = ((readData[7] << 8) | readData[8]);//系统电压
            quint16 cur = ((readData[9] << 8) | readData[10]);//系统电流
            quint16 pw = ((readData[11] << 8) | readData[12]);//系统功率
            quint16 vr = ((readData[13] << 8) | readData[14]);//电位器
            quint16 cpu = ((readData[15] << 8) | readData[16]);//cpu
            ui->pushButton_temp->setText(QString::asprintf("%.1f",temp/100.0) + "℃");
            ui->pushButton_hum->setText(QString::asprintf("%.1f",hum/100.0) + "%");
            ui->pushButton_cpu->setText(QString::asprintf("%.1f",cpu/100.0) + "℃");
            ui->pushButton_vr->setText(QString::asprintf("%.2f",vr/100.0) + "V");
            ui->pushButton_vol->setText(QString::asprintf("%.2f",vol/100.0) + "V");
            ui->pushButton_cur->setText(QString::asprintf("%.0f",cur/1.0) + "mA");
            ui->pushButton_pw->setText(QString::asprintf("%.2f",pw/1000.0) + "W");
        }
        else
        {
            qDebug() << "serial timeout";
        }
    }
}

void Widget::initUi()
{
    // 绘制背景图片
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(QString::fromUtf8(":/images/back.png"));
    QImage pix = ImgAllbackground.scaled(this->size(),Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(pix));
    this->setPalette(PAllbackground);

    // 设置 tabwidget 透明
    ui->tabWidget->setStyleSheet("QTabWidget::pane { background: transparent;border: none; }");
    ui->tabWidget->tabBar()->hide() ; // 隐藏标签项
    ui->tabWidget->setCurrentIndex(0);

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

    // 设置 listwidget 的样式表
    ui->listWidget->setStyleSheet("QListWidget { background: transparent;"
                                  "border: none; "
                                  "outline: none;"
                                  "font-size: 22px; "
                                  "color: white; "
                                  "font-weight: bold;"
                                  "padding-left: 5px;"
                                  "padding-right: 5px;"
                                  "padding-top: 50px;}"
                                  "QListWidget::item { min-height: 100px;"
                                  "color:white;"
                                  "border: none; }"
                                  "QListWidget::item:selected {min-height: 80px;"
                                  "color:white;"
                                  "background: #5354cb;"
                                  "border: none; "
                                  "border-radius: 5px; }"
                                  );
    //往下拉列表添加元素
    QListWidgetItem * modbus =  new QListWidgetItem(QIcon(":/images/modbus.png"),"STM32 | Modbus", ui->listWidget);
    ui->listWidget->addItem(modbus);
    QListWidgetItem * mqtt =  new QListWidgetItem(QIcon(":/images/mqtt.png"),"STM32 | MQTT", ui->listWidget);
    ui->listWidget->addItem(mqtt);
    QListWidgetItem * canopen =  new QListWidgetItem(QIcon(":/images/canopen.png"),"STM32 | CANOpen", ui->listWidget);
    ui->listWidget->addItem(canopen);
    ui->listWidget->setCurrentItem(modbus);//默认

    //向tabwidget 添加界面
    MQTT *Mqtt =  new MQTT(this);
    ui->tabWidget->addTab(Mqtt,"MQTT");
    CANOpen *Canopen =  new CANOpen(this);
    ui->tabWidget->addTab(Canopen,"CANOpen");

    ui->tabWidget->setStyleSheet("QTabWidget::pane { background: transparent;border: none; }");
    ui->tabWidget->tabBar()->hide() ; // 隐藏标签项
    ui->tabWidget->setCurrentIndex(0);
}


void Widget::on_listWidget_clicked(const QModelIndex &index)
{
    //qDebug() << "on_listWidget_itemClicked";
    ui->tabWidget->setCurrentIndex(index.row());//选择子窗体
}

