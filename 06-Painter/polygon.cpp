#include "polygon.h"
#include "ui_polygon.h"

polygon::polygon(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::polygon)
{
    ui->setupUi(this);
}

polygon::~polygon()
{
    delete ui;
}

qint32 polygon::getPointNum()
{
    qDebug() << "index=" << ui->comboBox->currentIndex();
    return ui->comboBox->currentIndex() + 3;
}

void polygon::on_pushButton_ok_clicked()
{
    // 发送一个信号
    emit add_newpolygon();
    qDebug()<<"add_newpolygon() 信号被发送";
    this->hide();// 隐藏窗口
}

void polygon::on_pushButton_esc_clicked()
{
    this->close();
}

