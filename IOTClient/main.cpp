#include "modbus.h"

#include <QApplication>
#include <QStyleFactory>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    a.setStyle(QStyleFactory::create("fusion"));

    //QFile file(":/qss/silvery.css");
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    Widget w;
    w.show();
    return QApplication::exec();
}
