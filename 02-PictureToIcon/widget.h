#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_pushButton_select_clicked();

    void on_pushButton_preview_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::Widget *ui;
    qint32 width;       //定义图片缩放宽度
    qint32 height;      //定义图片缩放高度
    QString fileName;   //保存文件名
};
#endif // WIDGET_H
