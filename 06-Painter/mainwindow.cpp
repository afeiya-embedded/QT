#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),set("config.ini",QSettings::IniFormat)
{
    ui->setupUi(this);
    fileName = (":/images/preview.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";

    QPainter painter(this);
    if(!fileName.isEmpty())
    {
        QPixmap map(fileName);
        if(!map.isNull())
        {
            //painter.drawPixmap(QPoint(0,0), map);
            // 拉伸铺满整个窗口（会变形）
            painter.drawPixmap(rect(),map.scaled(rect().size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        }
    }

    // // 构造函数里
    // auto *label = new QLabel(centralWidget());
    // label->setPixmap(QPixmap(fileName));
    // label->setScaledContents(true);   // ← 核心，自动跟随控件尺寸缩放
    // label->setAlignment(Qt::AlignCenter);

    // auto *lay = new QVBoxLayout(centralWidget());
    // lay->setContentsMargins(0, 0, 0, 0);
    // lay->addWidget(label);

    if(drawLineFlag)        //设置画线笔属性
    {
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawLine(line);
        painter.drawEllipse(line.p1(), 4, 4);
        painter.drawEllipse(line.p2(), 4, 4);

        set.beginGroup("line1");
        set.setValue("x1",line.p1().x());
        set.setValue("y1",line.p1().y());
        set.setValue("x2",line.p2().x());
        set.setValue("y2",line.p2().y());
        set.endGroup();
    }
    if(drawPolygonFlag)        //设置画多边形笔属性
    {
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPolygon(ply);
        for(int i = 0; i < ply.size(); i++)
        {
            painter.drawEllipse(ply.at(i), 4, 4);
        }

        set.beginGroup("polygon1");
        for(int i = 0; i < ply.size(); i++)
        {
            set.setValue(tr("x%0").arg(i), ply.at(i).x());
            set.setValue(tr("y%0").arg(i), ply.at(i).y());
        }
        set.endGroup();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) // 鼠标按下事件
{
    if(event->button() == Qt::LeftButton){ // 如果是鼠标左键按下
        qDebug()<<"鼠标左键被按下";
        qDebug()<<"鼠标被单击:"<<event->pos(); // 打印鼠标的位置

        //线段
        //鼠标位置与线点的位置保持10以内误差 即点击了这个点
        linePointIndex = -1;
        if( (abs(event->pos().x() - line.p1().x()) < 10) &&
            (abs(event->pos().y() - line.p1().y()) < 10) )
        {
            qDebug() << "p1 选中了";
            linePointIndex = 1;
            setCursor(Qt::CrossCursor);     //设置十字光标
        }
        else if( (abs(event->pos().x() - line.p2().x()) < 10) &&
                 (abs(event->pos().y() - line.p2().y()) < 10) )
        {
            qDebug() << "p2 选中了";
            linePointIndex = 2;
            setCursor(Qt::CrossCursor);     //设置十字光标
        }
        else
        {
            setCursor(Qt::ArrowCursor);     //设置正常光标
        }


        //多边形
        //鼠标位置与线点的位置保持10以内误差 即点击了这个点
        polygonPointIndex = -1;
        for(int i = 0; i <  ply.size(); i++)
        {
            if( (abs(event->pos().x() - ply.at(i).x()) < 10) &&
                (abs(event->pos().y() - ply.at(i).y()) < 10) )
            {
                qDebug() << "p1 选中了";
                polygonPointIndex = i;
                setCursor(Qt::CrossCursor);     //设置十字光标
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) // 鼠标释放事件
{
    // 释放鼠标后 , 要恢复鼠标的形状
    setCursor(Qt::ArrowCursor); // 正常鼠标样式
}

// 可设置单击后移动, 认为是鼠标移动
// 也可以实时的捕捉
void MainWindow::mouseMoveEvent(QMouseEvent *event) // 鼠标移动事件
{
    qDebug()<<"鼠标移动";

    if(!(event->buttons() & Qt::LeftButton))
    {
        return;
    }
    const QPoint pos = event->pos();
    if(linePointIndex == 1)
    {
        line.setP1(pos);
    }
    else if(linePointIndex == 2)
    {
        line.setP2(pos);
    }
    if(polygonPointIndex >= 0 && polygonPointIndex < ply.size())
    {
        ply.replace(polygonPointIndex, pos);
    }
    if(linePointIndex >= 0 || polygonPointIndex >= 0)
    {
        update();
    }
}

void MainWindow::on_action_load_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("打开 文件"), ".", "File(*.png *.jpg *.bmp);;");
    if(file.isEmpty())
    {
        return;
    }
    fileName = file;
    //产生paintEvent
    update();
}


void MainWindow::on_action_line_triggered()
{
    drawLineFlag = true;
    // 如果系统已经保存了 line的信息, 则需要自动加载线的信息
    // 如果没有保存, 则使用默认的线信息
    // 创建一个config.ini文件 , 文件不存在则创建, 文件存在则打开
    QSettings set("config.ini",QSettings::IniFormat);
    set.beginGroup("line1");// 开始的组
    //如果Line1有x1 这个key , 说明我们配置文件中已经保存了线 , 此时就需要我们加载即可
    if(set.contains("x1")) // 可以在config.ini 进行搜索 , 找到和没找到两种
    {
        qint32 x1 = set.value("x1").toInt();
        qint32 y1 = set.value("y1").toInt();
        qint32 x2 = set.value("x2").toInt();
        qint32 y2 = set.value("y2").toInt();
        line.setLine(x1,y1,x2,y2);
    }
    else // 如果没有就创建 这些值
    {
        qint32 x1 = 100;
        qint32 y1 = 100;
        qint32 x2 = 200;
        qint32 y2 = 200;
        line.setLine(x1,y1,x2,y2);
        set.setValue("x1",x1);
        set.setValue("y1",y1);
        set.setValue("x2",x2);
        set.setValue("y2",y2);
    }
    set.endGroup();

    update();
}

void MainWindow::add_newpolygon_slot()
{
    qDebug() << "add_newpolygon_slot";
    if(polygonP != nullptr)
    {
        ply.clear();
        qint32 n = polygonP->getPointNum();
        set.beginGroup("polygon1");// 开始的组
        //如果Line1有x1 这个key , 说明我们配置文件中已经保存了线 , 此时就需要我们加载即可
        if(set.contains("x1")) // 可以在config.ini 进行搜索 , 找到和没找到两种
        {
            for(int i = 0; i < n; i++)
            {
                qint32 x = set.value(tr("x%0").arg(i)).toInt();
                qint32 y = set.value(tr("y%0").arg(i)).toInt();
                ply.append(QPoint(x,y));
            }
        }
        else // 如果没有就创建 这些值
        {
            qint32 xx[]={208,514,804,743,568,239,140,120,100,80};
            qint32 yy[]={289,208,344,673,772,712,280,240,200,160};
            for(int i = 0; i < n; i++)
            {
                set.setValue(tr("x%0").arg(i), xx[i]);
                set.setValue(tr("y%0").arg(i), yy[i]);
                ply.append(QPoint(xx[i], yy[i]));
            }
        }
        set.endGroup();

        //产生paintEvent
        update();
    }

}

void MainWindow::on_action_polygon_triggered()
{
    if(polygonP == nullptr)
    {
        drawPolygonFlag = true;
        polygonP = new polygon();
        connect(polygonP, &polygon::add_newpolygon, this, &MainWindow::add_newpolygon_slot);
        polygonP->show();
    }
    else
    {
        drawPolygonFlag = true;
        polygonP->show();
    }
}


void MainWindow::on_action_clear_triggered()
{
    set.remove("line1");
    set.remove("polygon1");
    ply.clear();
    drawLineFlag = false;
    drawPolygonFlag = false;
    update();
}

