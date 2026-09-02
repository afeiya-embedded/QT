#ifndef POLYGON_H
#define POLYGON_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class polygon;
}

class polygon : public QWidget
{
    Q_OBJECT

public:
    explicit polygon(QWidget *parent = nullptr);
    ~polygon();

    qint32 getPointNum();

signals:
    void add_newpolygon(); // 自定义信号

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_esc_clicked();

private:
    Ui::polygon *ui;
};

#endif // POLYGON_H
