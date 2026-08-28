/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_16;
    QRadioButton *radioButton_32;
    QRadioButton *radioButton_64;
    QRadioButton *radioButton_128;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_select;
    QPushButton *pushButton_preview;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_save;
    QLabel *label_6;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 400);
        Widget->setMinimumSize(QSize(800, 400));
        Widget->setMaximumSize(QSize(800, 400));
        QFont font;
        font.setPointSize(12);
        Widget->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 90, 30));
        QFont font1;
        font1.setPointSize(10);
        label->setFont(font1);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(110, 10, 620, 60));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_16 = new QRadioButton(groupBox);
        radioButton_16->setObjectName(QString::fromUtf8("radioButton_16"));

        horizontalLayout->addWidget(radioButton_16);

        radioButton_32 = new QRadioButton(groupBox);
        radioButton_32->setObjectName(QString::fromUtf8("radioButton_32"));

        horizontalLayout->addWidget(radioButton_32);

        radioButton_64 = new QRadioButton(groupBox);
        radioButton_64->setObjectName(QString::fromUtf8("radioButton_64"));

        horizontalLayout->addWidget(radioButton_64);

        radioButton_128 = new QRadioButton(groupBox);
        radioButton_128->setObjectName(QString::fromUtf8("radioButton_128"));

        horizontalLayout->addWidget(radioButton_128);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 100, 90, 30));
        label_2->setFont(font1);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 170, 90, 30));
        label_3->setFont(font1);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 240, 90, 30));
        label_4->setFont(font1);
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 310, 90, 30));
        label_5->setFont(font1);
        pushButton_select = new QPushButton(Widget);
        pushButton_select->setObjectName(QString::fromUtf8("pushButton_select"));
        pushButton_select->setGeometry(QRect(110, 90, 120, 50));
        pushButton_preview = new QPushButton(Widget);
        pushButton_preview->setObjectName(QString::fromUtf8("pushButton_preview"));
        pushButton_preview->setGeometry(QRect(110, 160, 120, 50));
        pushButton_delete = new QPushButton(Widget);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(110, 230, 120, 50));
        pushButton_save = new QPushButton(Widget);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(110, 300, 120, 50));
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(520, 120, 200, 200));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\345\233\276\347\211\207\345\260\272\345\257\270\357\274\232", nullptr));
        groupBox->setTitle(QString());
        radioButton_16->setText(QCoreApplication::translate("Widget", "16X16", nullptr));
        radioButton_32->setText(QCoreApplication::translate("Widget", "32X32", nullptr));
        radioButton_64->setText(QCoreApplication::translate("Widget", "64X64", nullptr));
        radioButton_128->setText(QCoreApplication::translate("Widget", "128X128", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\345\233\276\347\211\207\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\351\242\204\350\247\210\345\233\276\347\211\207\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\345\233\276\347\211\207\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\345\233\276\347\211\207\357\274\232", nullptr));
        pushButton_select->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        pushButton_preview->setText(QCoreApplication::translate("Widget", "\351\242\204\350\247\210\345\233\276\347\211\207", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\345\233\276\347\211\207", nullptr));
        pushButton_save->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\345\233\276\347\211\207", nullptr));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
