#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("无标题 - 记事本"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    QString name = fileName.isEmpty() ? tr("无标题") : QFileInfo(fileName).fileName();
    setWindowTitle("* " + name + tr(" - 记事本"));

    saveFlag = true;
}


void MainWindow::on_action_new_triggered()
{
    // if(!ui->textEdit->toPlainText().isEmpty()) //textedit 中有内容
    if(saveFlag)
    {
        //qDebug()<<"弹窗";
        QMessageBox msgBox;
        // 遗留问题1: 如何改变弹窗的尺寸, 目前改不了
        msgBox.setWindowTitle(tr("记事本"));
        //msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save); // 默认选择

        int ret = msgBox.exec();
        switch (ret)
        {
            case QMessageBox::Save:
                // Save was clicked
                on_action_save_triggered();
                // fileName 字符串清空
                fileName.clear();
                ui->textEdit->clear();
                this->setWindowTitle(tr("无标题")+tr(" - 记事本"));
                break;
            case QMessageBox::Discard:
                // Don't Save was clicked
                fileName.clear();
                ui->textEdit->clear();
                this->setWindowTitle(tr("无标题")+tr(" - 记事本"));
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                break;
            default:
                // should never be reached
                break;
        }
    }

    saveFlag = false;
}

void MainWindow::on_action_save_triggered()
{

    if(fileName.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, tr("保存 文件"), ".", tr("Files (*.txt);;"));
        if(fileName.isEmpty())
        {
            return;
        }
    }

    //qDebug() << "fileName=" << fileName;

    QFile file(fileName) ; // 创建一个文件对象
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text|QIODevice::Truncate))
    {
        return;
    }
    file.write(ui->textEdit->toPlainText().toUtf8());
    file.close();

    saveFlag = false;

    this->setWindowTitle(QFileInfo(fileName).fileName()+tr(" - 记事本"));
}

void MainWindow::on_action_open_triggered()
{
    if(saveFlag)    //saveFlag=true textEdit发生了改变 有新内容没有保存
    {
        QMessageBox msgBox;
        // 遗留问题1: 如何改变弹窗的尺寸, 目前改不了
        msgBox.setWindowTitle(tr("记事本"));
        //msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save); // 默认选择
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Save:
            // Save was clicked
            on_action_save_triggered();
            // fileName 字符串清空
            fileName.clear();
            ui->textEdit->clear();
            this->setWindowTitle(tr("无标题")+tr(" - 记事本"));
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            fileName.clear();
            ui->textEdit->clear();
            this->setWindowTitle(tr("无标题")+tr(" - 记事本"));
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            break;
        default:
            // should never be reached
            break;
        }
    }

    fileName = QFileDialog::getOpenFileName(this, tr("打开 文件"), tr("."), tr("Files (*.txt);;"));
    QFile file(fileName) ; // 创建一个文件对象
    // if (!file.open(QIODevice::ReadWrite | QIODevice::Text|QIODevice::Truncate))
    // {
    //     return;
    // }
    // file.write(ui->textEdit->toPlainText().toUtf8());
    // file.close();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    ui->textEdit->setPlainText(file.readAll());
    file.close();

    this->setWindowTitle(QFileInfo(fileName).fileName()+tr(" - 记事本"));

    saveFlag = false;
}


void MainWindow::on_action_saveas_triggered()
{
    fileName = QFileDialog::getSaveFileName(this, tr("保存 文件"), ".", tr("Files (*.txt);;"));
    if(fileName.isEmpty()) // 获取到文件名后, 才可以操作
    {
        return;
    }
    QFile file(fileName) ; // 创建一个文件对象
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text|QIODevice::Truncate))
    {
        return;
    }
    file.write(ui->textEdit->toPlainText().toUtf8());
    file.close();

    saveFlag = false;

    this->setWindowTitle(QFileInfo(fileName).fileName()+tr(" - 记事本"));
}


void MainWindow::on_action_print_triggered()
{
    QPrinter printer ; // 定义一个打印机
    QPrintDialog printDialog(&printer, this); // 定义一个打印对话窗口
    if (printDialog.exec() == QDialog::Accepted) { // 点击确定时, 开始打印
        // print ...
        ui->textEdit->print(&printer); // 把textedit中的内容打印
    }
}


void MainWindow::on_action_exit_triggered()
{
    this->close();
}


void MainWindow::on_action_copy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_action_cut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_action_paste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_action_redo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_action_undo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_action_font_triggered()
{
    bool ok;
    // 获取字体
    QFont font = QFontDialog::getFont(&ok, QFont("宋体", 16), this);
    if (ok)
    {
        // the user clicked OK and font is set to the font the user selected
    }
    else {
        // the user canceled the dialog; font is set to the initial
        // value, in this case Helvetica [Cronyx], 10
    }
    qDebug()<<"font="<<font;
    ui->textEdit->setFont(font); // 对选中的文本设置字体
}

void MainWindow::on_action_bold_triggered(bool checked)
{
    if(checked)     //checked=true 粗体
    {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
}


void MainWindow::on_action_italic_triggered(bool checked)
{
    if(checked)     //checked=true 斜体
    {
        ui->textEdit->setFontItalic(true);
    }
    else
    {
        ui->textEdit->setFontItalic(false);
    }
}


void MainWindow::on_action_underline_triggered(bool checked)
{
    if(checked)     //checked=true 下划线
    {
        ui->textEdit->setFontUnderline(true);
    }
    else
    {
        ui->textEdit->setFontUnderline(false);
    }
}

void MainWindow::on_action_notepad_triggered()
{
    QMessageBox::about(this,tr("记事本"),  tr("这是记事本 5.15.2 v1.1 "));
}


void MainWindow::on_action_qt_triggered()
{
    QMessageBox::aboutQt(this);
}

// 要实现关闭窗口时, 提示是否保存文件, 必须使用重新实现 QMainWindow中的一个方法 closeEvent
// 每次关闭窗口时, 发送一个事件QCloseEvent ,应用程序可以接收这个事件, 并对事件进行处理
void MainWindow::closeEvent(QCloseEvent *event)
{
    //qDebug()<<"closeEvent被触发";

    if(fileName.isEmpty()) // 文件名为空
    {
        // 且 textedit 中有内容, 需要弹窗, 提示是否需要保存
        if(!ui->textEdit->toPlainText().isEmpty()) //textedit 中有内容
        {
            // 弹窗
            qDebug()<<"要弹窗";
            QMessageBox msgBox;
            // 遗留问题1: 如何改变弹窗的尺寸, 目前改不了
            msgBox.setWindowTitle(tr("记事本"));
            //msgBox.setText("The document has been modified.");
            msgBox.setInformativeText("Do you want to save your changes?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save); // 默认选择
            int ret = msgBox.exec();
            switch (ret)
            {
            case QMessageBox::Save:
                // Save was clicked
                // 继续让事件传递下去
                event->accept();
                break;
            case QMessageBox::Discard:
                // Don't Save was clicked
                // 继续让事件传递下去
                event->accept();
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                event->ignore(); // 忽略关闭窗体的操作
                break;
            default:
                // should never be reached
                break;
            }
        }
        else // 文件名为空 , textedit没有内容, 不需要弹窗
        {
            //qDebug()<<"文件名为空 , textedit没有内容, 不需要弹窗";
        }
    }
    else // 文件名不为空
    {
        // 文件是否存盘
        // 文件是否保存标志位, true: 表示存盘 , false : 没有存盘
        if(!saveFlag) // 条件满足 , 表示没有存盘 , 需要弹窗提示保存
        {
            //qDebug()<<"文件名不为空 文件没有保存,需要弹窗";
            QMessageBox msgBox;
            // 遗留问题1: 如何改变弹窗的尺寸, 目前改不了
            //msgBox.setText("The document has been modified.");
            msgBox.setInformativeText("Do you want to save your changes?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save); // 默认选择
            int ret = msgBox.exec();
            switch (ret)
            {
            case QMessageBox::Save:
                // Save was clicked
                // 继续让事件传递下去
                event->accept();
                break;
            case QMessageBox::Discard:
                // Don't Save was clicked
                // 继续让事件传递下去
                event->accept();
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                event->ignore(); // 忽略关闭窗体的操作
                break;
            default:
                // should never be reached
                break;
            }
        }
        else // 文件已存盘
        {

        }
    }
}
void MainWindow::on_action_enlish_triggered(bool checked)
{
    if(checked)     //checked=true English
    {
        qDebug() << translator.load("translations/en_US.qm");
        QApplication::installTranslator(&translator);
        ui->retranslateUi(this);
    }
    else
    {
        QApplication::installTranslator(nullptr);
        ui->retranslateUi(this);
    }
}

