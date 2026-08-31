#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
// 启用高DPI缩放
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    a.setStyle(QStyleFactory::create("fusion")); // fusion 这个主题比较好看
    MainWindow w;
    w.show();
    return QApplication::exec();
}
