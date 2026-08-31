#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber->display("00:00.00");
    ui->pushButton_start->setText(tr("启动计时"));
    ui->pushButton_reset->setText(tr("复位计数"));

    timer = new QTimer(this);
    // 设置定时器的信号处理函数， 等价于linux c 的signal函数功能
    // 参数1 : 发送信号者 timer
    // 参数2 : 发送信号者 发送什么信号 , &类名::信号
    // 参数3 : 接收信号者 this, 就是这个应用程序MainWindow
    // 参数4 : 信号处理函数 用于自定义
    connect(timer,&QTimer::timeout,this ,&MainWindow::timeout_slot);

    // 启动定时器 , 10ms 执行一次信号处理函数
    //timer->start(10);

    model = new QStandardItemModel(this); // 定义一个数据结构 , 用来保存数据
    /*设置列字段名*/
    model->setColumnCount(2); // 设置这个数据模型为2列 , 设置 一行有2列
    model->setHeaderData(0,Qt::Horizontal, tr("序号")); // 第一列名 序号
    model->setHeaderData(1,Qt::Horizontal, tr("数值")); // 第二列名 数值

    // 把 数据模型和显示模型进行关联
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(199);
    //隐藏行号
    ui->tableView->verticalHeader()->setHidden(true);
    //设置选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性， 即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeout_slot()
{
    //qDebug() << "timeout_slot";
    msec++;
    if(msec >= 100)
    {
        msec = 0;
        sec++;
        if(sec >= 60)
        {
            sec = 0;
            min++;
            if(min >= 60)
            {
                min = 0;
            }
        }
    }
    // 拼接字符串 , 在数码管上显示数字的字符串
    ui->lcdNumber->display( QString::asprintf("%02d:%02d.%02d",min,sec,msec));
}

void MainWindow::on_pushButton_start_clicked(bool checked)
{
    //qDebug() << "on_pushButton_start_clicked: " << checked;

    if(checked)
    {
        if(timer != nullptr)
        {
            //启动定时器 , 10ms 执行一次信号处理函数
            timer->start(10);
        }
        if(language)
        {
            ui->pushButton_reset->setText(tr("计数"));
            ui->pushButton_start->setText("停止计数");
        }
        else
        {
            ui->pushButton_reset->setText(tr("Count"));
            ui->pushButton_start->setText("Stop Count");
        }
    }
    else
    {
        if(timer != nullptr)
        {
            timer->stop();
        }

        if(language)
        {
            ui->pushButton_reset->setText(tr("复位计数"));
            ui->pushButton_start->setText("开始计数");
        }
        else
        {
            ui->pushButton_reset->setText(tr("ResetCount"));
            ui->pushButton_start->setText("Start Count");
        }
    }
}


void MainWindow::on_pushButton_reset_clicked()
{
    if(ui->pushButton_start->isChecked())
    {
        qDebug() << QString::asprintf("%02d:%02d.%02d",min,sec,msec);
        /*设置一条数据*/
        // lineCount : 是数据的第几行
        // 0 : 第几列
        model->setItem(lineCount, 0, new QStandardItem(QString::asprintf("%03d",lineCount+1)));
        model->setItem(lineCount, 1, new QStandardItem(QString::asprintf("%02d:%02d.%02d",min,sec,msec)));
        model->item(lineCount, 0)->setTextAlignment(Qt::AlignCenter); // 设置文本居中对齐
        model->item(lineCount, 1)->setTextAlignment(Qt::AlignCenter); // 设置文本居中对齐
        ui->tableView->setModel(model) ; // 给tableview 安装一个模型 model
        lineCount++;
    }
    else
    {
        min = 0, sec = 0, msec = 0;
        ui->lcdNumber->display( QString::asprintf("%02d:%02d.%02d",min,sec,msec));
        model->removeRows(0,lineCount); // 从0行 一直删除到 指定的行
        lineCount = 0;
    }
}

void MainWindow::on_action_language_triggered()
{
    QTranslator translator; // 语言翻译类
    translator.load("translations/en_US.qm"); // 去当前目录下去查 , 05-Timer-Desktop_Qt_5_15_2_MSVC2019_64bit-Debug

    if(language)        //true: Enlish
    {
        language = false;
// 以下两种办法都可以, 静态方法更加适用
#if 1
        QApplication::installTranslator(&translator);
#else
        if(appPointer != nullptr)
        {
            appPointer->installTranslator(&translator); // 安装英文
        }
#endif
        ui->retranslateUi(this); // 重新初始化界面
        model->clear(); // 把model中的所有内容清空
        model->setColumnCount(2); // 设置列数 ,一共是2列
        model->setHeaderData(0,Qt::Horizontal,tr("Number")); // 第1列的列名
        model->setHeaderData(1,Qt::Horizontal,tr("Value")); // 第2列的列名
        ui->tableView->setModel(model);
    }
    else
    {
        language = true;
// 以下两种办法都可以, 静态方法更加适用
#if 1
        QApplication::installTranslator(nullptr);
#else
        if(appPointer != nullptr)
        {
            appPointer->installTranslator(NULL); // 不安装语言包, 使用默认语言中文
        }
#endif
        ui->retranslateUi(this);
        model->clear(); // 把model中的所有内容清空
        model->setColumnCount(2); // 设置 一行有2列
        model->setHeaderData(0,Qt::Horizontal, tr("序号")); // 第一列名 序号
        model->setHeaderData(1,Qt::Horizontal, tr("数值")); // 第二列名 数值
        ui->tableView->setModel(model);
    }

}

