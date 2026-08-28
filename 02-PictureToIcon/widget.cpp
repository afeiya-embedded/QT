#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //qDebug()<<"构造函数调用";
    //设置默认选项，把图片的尺寸默认设置为64X64
    ui->radioButton_64->setChecked(true);

}

Widget::~Widget()
{
    delete ui;
}

//
void Widget::on_pushButton_select_clicked()
{
    //qDebug()<<"pushButton_select函数调用";
    //检查按键是否按下
    if(ui->radioButton_16->isChecked())
    {
        qDebug()<<"16x16";
    }
    else if(ui->radioButton_32->isChecked())
    {
        qDebug()<<"32x32";
    }
    else if(ui->radioButton_64->isChecked())
    {
        qDebug()<<"64x64";
    }
    else if(ui->radioButton_128->isChecked())
    {
        qDebug()<<"128x128";
    }
}

