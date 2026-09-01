#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QFont>
#include <QFontDialog>
#include <QCloseEvent>
#include <QTranslator>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_textEdit_textChanged();

    void on_action_new_triggered();

    void on_action_save_triggered();

    void on_action_open_triggered();

    void on_action_saveas_triggered();

    void on_action_print_triggered();

    void on_action_exit_triggered();

    void on_action_copy_triggered();

    void on_action_cut_triggered();

    void on_action_paste_triggered();

    void on_action_redo_triggered();

    void on_action_undo_triggered();

    void on_action_font_triggered();

    void on_action_bold_triggered(bool checked);

    void on_action_italic_triggered(bool checked);

    void on_action_underline_triggered(bool checked);

    void on_action_qt_triggered();

    void on_action_notepad_triggered();

    void on_action_enlish_triggered(bool checked);

    // 声明一个父类的虚函数, 用子类替换父类的实现
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    bool saveFlag = false;      //false: 保存 true: 没保存
    QString fileName;           //文件名
    QTranslator translator;     //语言包
};
#endif // MAINWINDOW_H
