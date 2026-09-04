#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),set("config.ini",QSettings::IniFormat)
{
    ui->setupUi(this);

    // 获取主机的ip地址
    // hostname 就计算机名称
    qDebug() << "hostname:" << QHostInfo::localHostName() ; // 获取计算机名
    // 获取主机名的目的是为了获取主机的ip地址， 可以使用方法 fromName获取ip
    // fromName 函数实现了， 根据主机名获取主机的IP地址
    // fromName 返回值是 QHostInfo， 一个主机可以有很多个ip地址
    // 在使用 address 方法， 可以获取主机名的所有ip地址
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName()) ; // 获取很多个地址对象
    foreach (QHostAddress addr, info.addresses()) {
        qDebug() <<"addr.protocol() = " << addr.protocol() ;
        if(addr.protocol() == QAbstractSocket::IPv4Protocol) // 只获取IPV4协议的ip
        {
            qDebug() << "addr:" << addr;
            ui->comboBox_ip->addItem(addr.toString());
        }
    }
    ui->comboBox_port->setCurrentText("8080");

    ui->groupBox_remote->hide();

    //设置默认ascii
    ui->radioButton_recv_ascii->setChecked(true);
    ui->radioButton_send_ascii->setChecked(true);

    ui->textEdit_send->setText("hello, world!");

    //读取设置
    set.beginGroup("config.ini");
    if(set.contains("type"))
    {
        QString type = set.value("type").toString();
        QString ip = set.value("ip").toString();
        QString port = set.value("port").toString();

        if(type == "UDP")
        {
            ui->comboBox_type->setCurrentIndex(0);
        }
        else if(type == "TCP Client")
        {
            ui->comboBox_type->setCurrentIndex(1);
        }
        else if(type == "TCP Server")
        {
            ui->comboBox_type->setCurrentIndex(2);
        }
        ui->comboBox_ip->setCurrentText(ip);
        ui->comboBox_port->setCurrentText(port);
    }
    else
    {
        set.setValue("type", ui->comboBox_type->currentText());
        set.setValue("port", ui->comboBox_port->currentText());
        set.setValue("ip", ui->comboBox_ip->currentText());
    }
    set.endGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 把字符串转成16进制字符串
// str1 是ascii的字符串
// str2 是hex 的字符串
void MainWindow::convertAsciiToHex(const QString &str1, QString &str2)
{
    str2 = "";
    for(int i=0;i<str1.size();i++)
    {
        str2 += QString::asprintf("%02X",str1.at(i).toLatin1());
        if(i < (str1.size()-1) ) // 最后一个字符不加空格
        {
            str2 += " ";
        }
    }
}

// 把16进制的字符串 转成 ascii的字符串
// str1 是hex 的字符串
// str2 是ascii 的字符串
void MainWindow::convertHexToAscii(const QString &str1, QString &str2)
{
    str2 = "" ;
    QStringList list = str1.split(" ") ; // 使用空格进行拆分
    qDebug()<<"list="<<list ;
    for(int i=0;i<list.size();i++)
    {
        qDebug()<<"char="<< QString::asprintf("%c",list.at(i).toInt() ) ;
        qDebug()<<"list.at(i)="<<list.at(i) ;
        bool ok ;
        qDebug()<<"list.at(i).toint="<<list.at(i).toInt(&ok,16) ;
        str2 += QString::asprintf("%c",list.at(i).toInt(&ok,16) ) ;
    }
    qDebug()<<"str2="<<str2 ;
}

char convertCharToHex(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}

// 把16进制的字符串转成16进制的QByteArray
void MainWindow::convertStringToHex(const QString &str, QByteArray &byteData)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    byteData.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        } i
            ++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = convertCharToHex(hstr);
        lowhexdata = convertCharToHex(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        byteData[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    byteData.resize(hexdatalen);
}

void MainWindow::udp_readyRead_slot()
{
    qDebug() << "udp_readyRead_slot";
    if(udpSocket != nullptr)
    {
        //有效字节
        quint32 nbytes = udpSocket->pendingDatagramSize();
        udpSocket->readDatagram(recvBuf, nbytes);

        if(ui->radioButton_recv_ascii->isChecked())
        {
            ui->textEdit_recv->insertPlainText(QString(recvBuf));
            ui->textEdit_recv->insertPlainText("\n");
        }
        else if(ui->radioButton_recv_hex->isChecked())
        {
            QString str2;
            convertAsciiToHex(QString(recvBuf), str2);
            ui->textEdit_recv->insertPlainText(QString(str2));
            ui->textEdit_recv->insertPlainText("\n");
        }
    }
}


void MainWindow::tcp_readyRead_slot()
{
    if(tcpSocket != nullptr)
    {
        //有效字节
        QByteArray data = tcpSocket->readAll();

        if(ui->radioButton_recv_ascii->isChecked())
        {
            ui->textEdit_recv->insertPlainText(QString(data));
            ui->textEdit_recv->insertPlainText("\n");
        }
        else if(ui->radioButton_recv_hex->isChecked())
        {
            QString str2;
            convertAsciiToHex(QString(data), str2);
            ui->textEdit_recv->insertPlainText(QString(str2));
            ui->textEdit_recv->insertPlainText("\n");
        }
    }
}

void MainWindow::tcp_connected_slot()
{
    qDebug() << "tcp_connected_slot";
    ui->pushButton_open->setIcon(QIcon(QString::fromUtf8(":/images/open.png")));
    ui->pushButton_open->setEnabled(true);
}

void MainWindow::tcp_errorOccurred_slot(QAbstractSocket::SocketError socketError)
{
    qDebug() << "tcp_errorOccurred_slot";

    if(socketError == QAbstractSocket::ConnectionRefusedError)
    {
        ui->pushButton_open->setIcon(QIcon(QString::fromUtf8(":/images/close.png")));
        ui->comboBox_ip->setEnabled(true);
        ui->comboBox_port->setEnabled(true);
        ui->comboBox_type->setEnabled(true);

        //连接不了 按键抬起
        //重新进行连接
        ui->pushButton_open->setChecked(false);
        ui->pushButton_open->setEnabled(true);

        //释放tcp
        if(tcpSocket != nullptr)
        {
            tcpSocket->close();
            tcpSocket->deleteLater();
            tcpSocket = nullptr;
        }
    }
}

void MainWindow::tcpserver_readyRead_slot()
{
    for (int i = 0; i < tcpClients.count(); ++i) {
        if(tcpClients.at(i)->bytesAvailable() > 0)
        {
            QByteArray data = tcpClients.at(i)->readAll();

            if(ui->radioButton_recv_ascii->isChecked())
            {
                ui->textEdit_recv->insertPlainText(QString(data));
                ui->textEdit_recv->insertPlainText("\n");
            }
            else if(ui->radioButton_recv_hex->isChecked())
            {
                QString str2;
                convertAsciiToHex(QString(data), str2);
                ui->textEdit_recv->insertPlainText(QString(str2));
                ui->textEdit_recv->insertPlainText("\n");
            }
        }
    }
}

void MainWindow::tcpserver_disconnected_slot()
{
    qDebug() << "tcpserver_disconnected_slot";

    for (int i = 0; i < tcpClients.count(); ++i) {
        if(tcpClients.at(i)->state() == QAbstractSocket::UnconnectedState)
        {
            tcpClients.at(i)->close();
            tcpClients.remove(i);
            ui->comboBox_remote->removeItem(i);
        }
    }
}

void MainWindow::tcpserver_newConnection_slot()
{
    qDebug() << "tcpserver_newConnection_slot";
    if(tcpServer != nullptr)
    {
        //接收客户端的请求 进行处理
        QTcpSocket *client = tcpServer->nextPendingConnection();

        connect(client, &QTcpSocket::readyRead, this, &MainWindow::tcpserver_readyRead_slot);

        connect(client, &QTcpSocket::disconnected, this, &MainWindow::tcpserver_disconnected_slot);

        tcpClients.append(client);

        //获取客户端ip和port
        QHostAddress addr = client->peerAddress();
        quint16 port = client->peerPort();
        //显示远程主机信息
        ui->comboBox_remote->addItem(tr("%0:%1").arg(addr.toString()).arg(port));
    }
}

void MainWindow::on_pushButton_open_clicked(bool checked)
{
    qDebug() << "on_pushButton_open_clicked" << checked;

    //ui->comboBox_type->currentIndex = 0   UDP
    //ui->comboBox_type->currentIndex = 1   TCP Client
    //ui->comboBox_type->currentIndex = 2   TCP Server
    qDebug() << "ui->comboBox_type->currentIndex=" << ui->comboBox_type->currentIndex();

    if(ui->comboBox_type->currentText() == "UDP")           //UDP协议
    {
        qDebug() << "open=" << ui->comboBox_type->currentText();
        if(checked)     //open
        {
            ui->pushButton_open->setIcon(QIcon(QString::fromUtf8(":/images/open.png")));
            ui->comboBox_ip->setEnabled(false);
            ui->comboBox_port->setEnabled(false);
            ui->comboBox_type->setEnabled(false);

            //udp信号处理函数
            udpSocket = new QUdpSocket(this);
            connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::udp_readyRead_slot);
            QHostAddress addr(ui->comboBox_ip->currentText());
            quint16 port = ui->comboBox_port->currentText().toUShort();

            if(!udpSocket->bind(addr, port))
            {
                delete udpSocket;
                udpSocket = nullptr;
                ui->pushButton_open->setChecked(false);
                return;
            }

            qDebug() << "ui->comboBox_port->currentText()=" << port;
            //设置远程主机
            ui->comboBox_remote->setCurrentText(tr("%0:%1")
                                                .arg(ui->comboBox_ip->currentText())
                                                .arg(ui->comboBox_port->currentText())
                                                );
            ui->groupBox_remote->show();

            //保存设置
            set.beginGroup("config.ini");
            set.setValue("type", ui->comboBox_type->currentText());
            set.setValue("port", ui->comboBox_port->currentText());
            set.setValue("ip", ui->comboBox_ip->currentText());
            set.endGroup();
        }
        else
        {
            ui->pushButton_open->setIcon(QIcon(QString::fromUtf8(":/images/close.png")));
            ui->comboBox_ip->setEnabled(true);
            ui->comboBox_port->setEnabled(true);
            ui->comboBox_type->setEnabled(true);

            ui->groupBox_remote->hide();

            //释放udp
            if(udpSocket != nullptr)
            {
                udpSocket->close();
                udpSocket->deleteLater();
                udpSocket = nullptr;
            }
        }
    }
    else if(ui->comboBox_type->currentText() == "TCP Client")       //TCP Client协议
    {
        if(checked)     //open
        {
            //tcp信号处理函数
            tcpSocket = new QTcpSocket(this);

            //连接服务器
            connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::tcp_readyRead_slot);
            connect(tcpSocket, &QTcpSocket::connected, this, &MainWindow::tcp_connected_slot);
            connect(tcpSocket, &QTcpSocket::errorOccurred, this, &MainWindow::tcp_errorOccurred_slot);


            QHostAddress addr(ui->comboBox_ip->currentText());
            quint16 port = ui->comboBox_port->currentText().toUShort();
            tcpSocket->connectToHost(addr, port);

            ui->comboBox_ip->setEnabled(false);
            ui->comboBox_port->setEnabled(false);
            ui->comboBox_type->setEnabled(false);
            ui->pushButton_open->setEnabled(false);

            //保存设置
            set.beginGroup("config.ini");
            set.setValue("type", ui->comboBox_type->currentText());
            set.setValue("port", ui->comboBox_port->currentText());
            set.setValue("ip", ui->comboBox_ip->currentText());
            set.endGroup();

        }
        else
        {
            ui->pushButton_open->setIcon(QIcon(QString::fromUtf8(":/images/close.png")));
            ui->comboBox_ip->setEnabled(true);
            ui->comboBox_port->setEnabled(true);
            ui->comboBox_type->setEnabled(true);

            ui->groupBox_remote->hide();
        }
    }
    else if(ui->comboBox_type->currentText() == "TCP Server")       //TCP Server协议
    {
        qDebug() << "TCP Server";

        if(checked)     //open
        {
            //tcp信号处理函数
            tcpServer = new QTcpServer(this);

            //连接服务器
            connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::tcpserver_newConnection_slot);

            QHostAddress addr(ui->comboBox_ip->currentText());
            quint16 port = ui->comboBox_port->currentText().toUShort();

            if(tcpServer->listen(addr, port))
            {
                ui->pushButton_open->setIcon(QIcon(QString::fromUtf8(":/images/open.png")));
                ui->comboBox_ip->setEnabled(false);
                ui->comboBox_port->setEnabled(false);
                ui->comboBox_type->setEnabled(false);
                ui->pushButton_open->setText(tr("关闭"));

                ui->groupBox_remote->show();

                //保存设置
                set.beginGroup("config.ini");
                set.setValue("type", ui->comboBox_type->currentText());
                set.setValue("port", ui->comboBox_port->currentText());
                set.setValue("ip", ui->comboBox_ip->currentText());
                set.endGroup();
            }
            else
            {
                // qDebug() << "TCP Server listen";

                if(tcpServer != nullptr)
                {
                    tcpServer->close();
                    tcpServer->deleteLater();
                    tcpServer = nullptr;
                }
                ui->pushButton_open->setChecked(false);

                ui->groupBox_remote->show();
            }

        }
        else
        {
            ui->pushButton_open->setIcon(QIcon(QString::fromUtf8(":/images/close.png")));
            ui->comboBox_ip->setEnabled(true);
            ui->comboBox_port->setEnabled(true);
            ui->comboBox_type->setEnabled(true);
            ui->pushButton_open->setText(tr("打开"));

            ui->groupBox_remote->hide();
            //释放udp
            if(tcpServer != nullptr)
            {
                tcpServer->close();
                tcpServer->deleteLater();
                tcpServer = nullptr;
            }
        }
    }
}

void MainWindow::on_pushButton_send_clicked()
{
    if(ui->comboBox_type->currentText() == "UDP")
    {
        //判断能不能发送数据
        if(!ui->pushButton_open->isChecked())
        {
            return;
        }

        QString ip_port = ui->comboBox_remote->currentText();
        QStringList list = ip_port.split(":");
        foreach (QString l, list) {
            qDebug() <<"l:" << l;
        }
        QHostAddress addr(list[0]);
        quint16 port = list[1].toShort();
        if(ui->radioButton_send_ascii->isChecked())         //发送ascii
        {
            if(udpSocket != nullptr)
            {
                udpSocket->writeDatagram(ui->textEdit_send->toPlainText().toUtf8(), addr, port);
            }
        }
        else if(ui->radioButton_send_hex->isChecked())
        {
            QByteArray data;
            convertStringToHex(ui->textEdit_send->toPlainText(), data);
            if(tcpSocket != nullptr)
            {
                tcpSocket->write(data);
            }
        }
    }
    else if(ui->comboBox_type->currentText() == "TCP Client")
    {
        //判断能不能发送数据
        if(!ui->pushButton_open->isChecked())
        {
            return;
        }

        if(ui->radioButton_send_ascii->isChecked())         //发送ascii
        {
            if(tcpSocket != nullptr)
            {
                tcpSocket->write(ui->textEdit_send->toPlainText().toUtf8());
            }
        }
        else if(ui->radioButton_send_hex->isChecked())
        {
            QByteArray data;
            convertStringToHex(ui->textEdit_send->toPlainText(), data);
            if(tcpSocket != nullptr)
            {
                tcpSocket->write(data);
            }
        }
    }
    else if(ui->comboBox_type->currentText() == "TCP Server")
    {
        //判断能不能发送数据
        if(!ui->pushButton_open->isChecked())
        {
            return;
        }

        for (int i = 0; i < tcpClients.count(); ++i) {
            QString info = tr("%0:%1")
                               .arg(tcpClients.at(i)->peerAddress().toString())
                               .arg(tcpClients.at(i)->peerPort());

            qDebug() << "info=" << info;
            if(info == ui->comboBox_remote->currentText())
            {
                if(ui->radioButton_send_ascii->isChecked())         //发送ascii
                {
                    if(tcpClients.at(i) != nullptr)
                    {
                        tcpClients.at(i)->write(ui->textEdit_send->toPlainText().toUtf8());
                    }
                }
                else if(ui->radioButton_send_hex->isChecked())
                {
                    QByteArray data;
                    convertStringToHex(ui->textEdit_send->toPlainText(), data);
                    if(tcpClients.at(i) != nullptr)
                    {
                        tcpClients.at(i)->write(data);
                    }
                }
            }
        }


    }

}


void MainWindow::on_radioButton_send_hex_clicked()
{
    if(sendHexAsciiFlag)        //ascii --> hex
    {
        QString str2;
        convertAsciiToHex(ui->textEdit_send->toPlainText(), str2);
        ui->textEdit_send->setText(str2);
        sendHexAsciiFlag = false;
    }
}


void MainWindow::on_radioButton_send_ascii_clicked()
{
    if(!sendHexAsciiFlag)        //hex --> ascii
    {
        QString str2;
        convertHexToAscii(ui->textEdit_send->toPlainText(), str2);
        ui->textEdit_send->setText(str2);
        sendHexAsciiFlag = true;
    }
}


void MainWindow::on_pushButton_recv_clear_clicked()
{
    ui->textEdit_recv->clear();
}


void MainWindow::on_pushButton_send_clear_clicked()
{
    ui->textEdit_send->clear();
}


void MainWindow::on_comboBox_type_activated(int index)
{
    if(index == 0)
    {
        ui->label_ip->setText("2.本机主机地址");
        ui->label_port->setText("3.本机主机端口");
        ui->pushButton_open->setText("打开");
    }
    else if(index == 1)
    {
        ui->label_ip->setText("2.远程主机地址");
        ui->label_port->setText("3.远程主机端口");
        ui->pushButton_open->setText("连接");
    }
    else
    {
        ui->label_ip->setText("2.本机主机地址");
        ui->label_port->setText("3.本机主机端口");
        ui->pushButton_open->setText("打开");
    }
}

