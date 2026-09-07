#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList lists = QSqlDatabase::drivers() ;
    foreach (QString l, lists) {
        qDebug()<<"支持的数据库驱动为:" << l ;
    }
    // 运行软件时打开数据库
    db = QSqlDatabase::addDatabase("QMYSQL"); // 设置要打开数据库的类型, 这个类型必须是支持的类型
    db.setDatabaseName("student"); // 要打开的数据库名字 , mysql 数据库中不允续有后缀名 student.db , 省略写法为student
    db.setHostName("localhost"); // 计算机名称, localhost 是本机ip
    db.setPort(3306); // 设置mysqld 后台服务器的端口
    db.setUserName("root"); // 设置mysql登录的用户名
    db.setPassword("123456"); // 设置mysql登录的密码
    bool ok = db.open(); // 有数据库就打开, 不存在就创建
    if(!ok) // 打开数据库失败
    {
        QMessageBox::warning(this,tr("mysql"),tr("student.db数据库打开失败"));
    }
    qDebug()<<"1:***************";

    // 登录数据库后, 要先创建一个数据库
    // 登陆数据库成功后 ,要先创建一个数据库 , 可以使用命令
    // mysql -u root -p
    // 输入密码:123456
    // create DATABASE student;
    // 注意 命令要有一个 ";" 作为结束符
    // 数据库不能以.db形式出现 , 不能有后缀名
    // 选择要使用的数据库
    QSqlQuery query(db); // 要使用哪一个数据库实例
    QString sql = tr("use student;"); // 指定要选择的数据库
    ok = query.exec(sql); // 执行sql语句
    if(!ok)
    {
        QMessageBox::warning(this,"use student","语法错误");
    }

    model = new QStandardItemModel(this); // 定义一个数据结构 , 用来保存数据
    /*设置列字段名*/
    model->setColumnCount(5); // 设置这个数据模型5列 ,
    model->setHeaderData(0,Qt::Horizontal, tr("学号")); // 第1列名 学号
    model->setHeaderData(1,Qt::Horizontal, tr("名字")); // 第2列名 名字
    model->setHeaderData(2,Qt::Horizontal, tr("性别")); // 第3列名 性别
    model->setHeaderData(3,Qt::Horizontal, tr("年龄")); // 第4列名 年龄
    model->setHeaderData(4,Qt::Horizontal, tr("成绩")); // 第5列名 成绩

    // 把 数据模型和显示模型进行关联
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(ui->tableView->size().width()/5);
    //隐藏行号
    ui->tableView->verticalHeader()->setHidden(true);
    //设置选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性， 即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    showAll();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_creat_clicked()
{
    // // 创建数据库的表
    // // 执行一个sql语句， 使用QSqlQuery
    // QString sql = "create table student(number int primary key,name char,gender char,age int,score float);" ;
    // QSqlQuery query ; //创建一个执行sql语句的对象
    // bool ok = query.exec(sql) ; // 执行数据库语句
    // if(!ok) // 执行sql语句失败
    // {
    //     // 获取错误信息
    //     qDebug() << query.lastError().text() ;
    //     QMessageBox::critical(this,tr("创建表错误"),query.lastError().text());
    //     return ;
    // }
    // else // 创建表成功
    // {
    //     QMessageBox::information(this,tr("创建数据库成功"),tr("创建student表成功"));
    // }


    // 创建数据库的表
    // 执行一个sql语句 , 使用qsqlquery
    // create table student(sn int primary key,name char(20),sex char(10),age int,score float)
    QString sql = "create table student(number int primary key,name char(20),gender char(10),age int,score float);";
    QSqlQuery query; // 创建一个执行sql语句的对象
    bool ok = query.exec(sql);
    if(!ok) // 执行sql 语句失败
    {
        qDebug()<<query.lastError().text();
        QMessageBox::critical(this,tr("创建表错误"),query.lastError().text());
        return ;
    }
    else
    {
        QMessageBox::information(this,tr("创建表成功"),tr("创建student表成功") );
    }
}

void Widget::showAll()
{
    model->removeRows(0,lineCount);
    lineCount = 0;

    // 创建数据库的表
    // 执行一个sql语句， 使用QSqlQuery
    QString sql = tr("select * from student;") ;
    QSqlQuery query ; //创建一个执行sql语句的对象
    bool ok = query.exec(sql) ; // 执行数据库语句
    if(!ok) // 执行sql语句失败
    {
        // 获取错误信息
        qDebug() << query.lastError().text() ;
        QMessageBox::critical(this,tr("查询记录错误"),query.lastError().text());
        return ;
    }
    else // 创建表成功
    {
        while(query.next())
        {
            qDebug() << "number=" << query.value(0).toUInt();
            qDebug() << "  name=" << query.value(1).toString();
            qDebug() << "   sex=" << query.value(2).toString();
            qDebug() << "   age=" << query.value(3).toUInt();
            qDebug() << " score=" << query.value(4).toFloat();

            if(model != nullptr)
            {
                for (int i = 0; i < model->columnCount(); ++i) {
                    model->setItem(lineCount, i, new QStandardItem(query.value(i).toString()));
                    //居中对齐
                    model->item(lineCount, i)->setTextAlignment(Qt::AlignCenter);
                }
                ui->tableView->setModel(model);
                lineCount++;
            }
        }
    }
}

void Widget::on_pushButton_insert_clicked()
{
    // 创建数据库的表
    // 执行一个sql语句， 使用QSqlQuery
    QString sql = tr("insert into student values(%0,'%1','%2',%3,%4);")
                    .arg(ui->lineEdit_number->text().toUInt())
                    .arg(ui->lineEdit_name->text())
                    .arg(ui->comboBox_sex->currentText())
                    .arg(ui->lineEdit_age->text().toUInt())
                    .arg(ui->lineEdit_score->text().toFloat());

    QSqlQuery query ; //创建一个执行sql语句的对象
    bool ok = query.exec(sql) ; // 执行数据库语句
    if(!ok) // 执行sql语句失败
    {
        // 获取错误信息
        qDebug() << query.lastError().text() ;
        QMessageBox::critical(this,tr("插入记录错误"),query.lastError().text());
        return ;
    }
    else // 插入记录成功
    {
        //QMessageBox::information(this,tr("插入记录成功"),tr("创建student表成功"));
        showAll();
    }
}


void Widget::on_pushButton_show_clicked()
{
    showAll();
}


void Widget::on_pushButton_search_clicked()
{
    model->removeRows(0,lineCount);
    lineCount = 0;

    // 创建数据库的表
    // 执行一个sql语句， 使用QSqlQuery
    QString sql = tr("select * from student where number = %0;")
                      .arg(ui->lineEdit_number->text().toUInt());
    QSqlQuery query ; //创建一个执行sql语句的对象
    bool ok = query.exec(sql) ; // 执行数据库语句
    if(!ok) // 执行sql语句失败
    {
        // 获取错误信息
        qDebug() << query.lastError().text() ;
        QMessageBox::critical(this,tr("查询记录错误"),query.lastError().text());
        return ;
    }
    else // 创建表成功
    {
        while(query.next())
        {
            qDebug() << "number=" << query.value(0).toUInt();
            qDebug() << "  name=" << query.value(1).toString();
            qDebug() << "   sex=" << query.value(2).toString();
            qDebug() << "   age=" << query.value(3).toUInt();
            qDebug() << " score=" << query.value(4).toFloat();

            if(model != nullptr)
            {
                for (int i = 0; i < model->columnCount(); ++i) {
                    model->setItem(lineCount, i, new QStandardItem(query.value(i).toString()));
                    //居中对齐
                    model->item(lineCount, i)->setTextAlignment(Qt::AlignCenter);
                }
                ui->tableView->setModel(model);
                lineCount++;
            }
        }
    }
}


void Widget::on_pushButton_delete_clicked()
{
    // 创建数据库的表
    // 执行一个sql语句， 使用QSqlQuery
    QString sql = tr("delete from student where number = %0 ;")
                      .arg(ui->lineEdit_number->text().toUInt());

    QSqlQuery query ; //创建一个执行sql语句的对象
    bool ok = query.exec(sql) ; // 执行数据库语句
    if(!ok) // 执行sql语句失败
    {
        // 获取错误信息
        qDebug() << query.lastError().text() ;
        QMessageBox::critical(this,tr("删除记录错误"),query.lastError().text());
        return ;
    }
    else // 插入记录成功
    {
        //QMessageBox::information(this,tr("插入记录成功"),tr("创建student表成功"));
        showAll();
    }
}


void Widget::on_pushButton_modfiy_clicked()
{
    // 创建数据库的表
    // 执行一个sql语句， 使用QSqlQuery
    QString sql = tr("update student set name = '%0', gender = '%1', age = %2, score = %3 where number = %4;")
                      .arg(ui->lineEdit_name->text())
                      .arg(ui->comboBox_sex->currentText())
                      .arg(ui->lineEdit_age->text().toUInt())
                      .arg(ui->lineEdit_score->text().toFloat())
                      .arg(ui->lineEdit_number->text().toUInt());

    QSqlQuery query ; //创建一个执行sql语句的对象
    bool ok = query.exec(sql) ; // 执行数据库语句
    if(!ok) // 执行sql语句失败
    {
        // 获取错误信息
        qDebug() << query.lastError().text() ;
        QMessageBox::critical(this,tr("修改记录错误"),query.lastError().text());
        return ;
    }
    else // 插入记录成功
    {
        showAll();
    }
}

