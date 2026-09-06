#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItem>

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

    void showAll();

private slots:
    void on_pushButton_creat_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_show_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_modfiy_clicked();

private:
    Ui::Widget *ui;

    QSqlDatabase db;                //数据库
    QStandardItemModel *model;      //数据模型
    quint32 lineCount = 0;

};
#endif // WIDGET_H
