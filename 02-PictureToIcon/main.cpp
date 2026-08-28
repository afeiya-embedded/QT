#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
// 启用高DPI缩放
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return QApplication::exec();
}
