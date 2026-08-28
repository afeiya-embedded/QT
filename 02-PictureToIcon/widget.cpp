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

void Widget::on_pushButton_select_clicked()
{
    //qDebug()<<"pushButton_select函数调用";
    //检查按键是否按下
    if(ui->radioButton_16->isChecked())
    {
        qDebug()<<"16x16";
        this->width = 16;
        this->height = 16;
    }
    else if(ui->radioButton_32->isChecked())
    {
        qDebug()<<"32x32";
        this->width = 32;
        this->height = 32;
    }
    else if(ui->radioButton_64->isChecked())
    {
        qDebug()<<"64x64";
        this->width = 64;
        this->height = 64;
    }
    else if(ui->radioButton_128->isChecked())
    {
        qDebug()<<"128x128";
        this->width = 128;
        this->height = 128;
    }

    fileName = QFileDialog::getOpenFileName(this, tr("打开 文件"), ".", tr("Image Files (*.png *.jpg *.bmp);;"));
    //qDebug()<<"filename: "<<fileName;
    if(fileName.isEmpty())
    {
        qDebug()<<"文件打开失败";
        ui->label_filemname->clear();
        ui->label_picture->clear();
        return;
    }

    QFileInfo fi(fileName);
    QString name = fi.fileName();
    qDebug()<<"name: "<<name;
    ui->label_filemname->setText(fileName);

    //创建图片对象
    QPixmap map(fileName);
    //图片进行缩放
    QPixmap newmap =  map.scaled(width, height);
    ui->label_picture->setPixmap(newmap);
}

void Widget::on_pushButton_preview_clicked()
{
    if(ui->radioButton_16->isChecked())
    {
        qDebug()<<"16x16";
        this->width = 16;
        this->height = 16;
    }
    else if(ui->radioButton_32->isChecked())
    {
        qDebug()<<"32x32";
        this->width = 32;
        this->height = 32;
    }
    else if(ui->radioButton_64->isChecked())
    {
        qDebug()<<"64x64";
        this->width = 64;
        this->height = 64;
    }
    else if(ui->radioButton_128->isChecked())
    {
        qDebug()<<"128x128";
        this->width = 128;
        this->height = 128;
    }

    //创建图片对象
    QPixmap map(fileName);
    //图片进行缩放
    QPixmap newmap =  map.scaled(width, height);
    ui->label_picture->setPixmap(newmap);
}


void Widget::on_pushButton_delete_clicked()
{
    ui->label_filemname->clear();
    ui->label_picture->clear();
    fileName.clear();
}


void Widget::on_pushButton_save_clicked()
{
    if(fileName.isEmpty())
    {
        return;
    }

    QString  saveFile = QFileDialog::getSaveFileName(this, tr("保存 文件"), ".", tr("Image Files (*.ico);;"));

    if(ui->radioButton_16->isChecked())
    {
        qDebug()<<"16x16";
        this->width = 16;
        this->height = 16;
    }
    else if(ui->radioButton_32->isChecked())
    {
        qDebug()<<"32x32";
        this->width = 32;
        this->height = 32;
    }
    else if(ui->radioButton_64->isChecked())
    {
        qDebug()<<"64x64";
        this->width = 64;
        this->height = 64;
    }
    else if(ui->radioButton_128->isChecked())
    {
        qDebug()<<"128x128";
        this->width = 128;
        this->height = 128;
    }

    //创建图片对象
    QPixmap map(fileName);
    //图片进行缩放
    QPixmap newmap =  map.scaled(width, height);
    newmap.save(saveFile);
}

