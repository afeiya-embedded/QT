#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>
#include <QDebug>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QSettings>

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

    void convertAsciiToHex(const QString &str1, QString &str2);

    void convertHexToAscii(const QString &str1, QString &str2);

    void convertStringToHex(const QString &str, QByteArray &byteData);

private slots:

    void on_pushButton_open_clicked(bool checked);

    void udp_readyRead_slot();

    void tcp_readyRead_slot();

    void tcp_connected_slot();

    void tcp_errorOccurred_slot(QAbstractSocket::SocketError socketError);

    void tcpserver_newConnection_slot();

    void tcpserver_readyRead_slot();

    void tcpserver_disconnected_slot();

    void on_pushButton_send_clicked();

    void on_radioButton_send_hex_clicked();

    void on_radioButton_send_ascii_clicked();

    void on_pushButton_recv_clear_clicked();

    void on_pushButton_send_clear_clicked();

    void on_comboBox_type_activated(int index);



private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    char recvBuf[1024] = {0};           //接收缓存区

    //false: ascii
    //true: hex
    bool sendHexAsciiFlag = false;      //发送格式标志位

    QSettings set;

    QVector<QTcpSocket*> tcpClients;         //tcp模板

};
#endif // MAINWINDOW_H
