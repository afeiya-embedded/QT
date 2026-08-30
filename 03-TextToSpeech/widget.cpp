#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList engines =  QTextToSpeech::availableEngines();  //获取有效引擎
    for(QString &engine : engines)
    {
        qDebug() << "engine:" << engine;
        ui->comboBox_engine->addItem(engine);
    }

    tts = new QTextToSpeech(this);      //创建tts对象
    ui->label_pitch->setNum(50);
    ui->label_rate->setNum(50);
    ui->label_volume->setNum(50);

    if(tts != nullptr)
    {
        QVector<QLocale> languages = tts->availableLocales();
        tts->setLocale(languages[0]);
        QVector<QVoice> voices = tts->availableVoices();
        tts->setVoice(voices[0]);
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_comboBox_engine_activated(int index)
{
    //qDebug() << "on_comboBox_engine_activated: " << index;
    ui->comboBox_language->clear();
    if(tts != nullptr)
    {
        QVector<QLocale> languages = tts->availableLocales();
        for(auto &local : languages)
        {
            qDebug()<<"local:"<<local; // 显示所有
            qDebug()<<"local language:"<<local.language(); // 显示语言
            qDebug()<<"local country :"<<local.country(); // 显示国家
            qDebug()<<"country :"<<QLocale::countryToString(local.country()); // 显示国家
            qDebug()<<"language:"<<QLocale::languageToString(local.language()); // 显示语言
            qDebug()<<"script :"<<QLocale::scriptToString(local.script()); // 显示描述信息
            ui->comboBox_language->addItem(QString(tr("%0-%1-%2")
                                                        .arg(QLocale::countryToString(local.country()))
                                                       .arg(QLocale::scriptToString(local.script()))
                                                       .arg(QLocale::languageToString(local.language()))
                                                   ),QVariant(local)
                                           );
        }
    }

}


void Widget::on_comboBox_language_activated(int index)
{
    qDebug() << "on_comboBox_engine_activated: " << index;

    ui->comboBox_name->clear();
    if(tts != nullptr)
    {
        tts->setLocale(ui->comboBox_language->currentData().toLocale());    //设置语言
        QVector<QVoice> voices = tts->availableVoices();
        for(QVoice voice:voices)
        {
            qDebug()<<"genderName :"<<QVoice::genderName(voice.gender()); // 显示性别
            qDebug()<<"name :"<<voice.name() ; // 显示姓名
            ui->comboBox_name->addItem(QString(tr("%0-%1)")
                                                     .arg(voice.name())
                                                     .arg(QVoice::genderName(voice.gender()))
                                               ));
        }
    }
}

void Widget::on_comboBox_name_activated(int index)
{
    if(tts != nullptr)
    {
        QVector<QVoice> voices = tts->availableVoices();
        tts->setVoice(voices[index]);
    }
}

void Widget::on_pushButton_paly_clicked()
{
    if(tts != nullptr)
    {
        //把textEdit播放出来
        tts->say(ui->textEdit->toPlainText());
    }
}

void Widget::on_pushButton_resume_clicked()
{
    if(tts != nullptr)
    {
        tts->resume();
    }
}


void Widget::on_pushButton_stop_clicked()
{
    if(tts != nullptr)
    {
        tts->stop();
    }
}

void Widget::on_pushButton_pause_clicked()
{
    if(tts != nullptr)
    {
        tts->pause();
    }
}

void Widget::on_horizontalSlider_rate_valueChanged(int value)
{
    ui->label_rate->setNum(value);
    if(tts != nullptr)
    {
        double newvalue = (value - 50) / 50.0 ; // -1.0 ~ 1.0
        tts->setRate(newvalue);// 设置播放语速
    }
}

void Widget::on_horizontalSlider_volume_valueChanged(int value)
{
    ui->label_volume->setNum(value);
    if(tts != nullptr)
    {
        double newvalue = value / 100.0; // 0.0 ~ 1.0
        tts->setVolume(newvalue);
    }
}

void Widget::on_horizontalSlider_pitch_valueChanged(int value)
{
    ui->label_pitch->setNum(value);
    if(tts != nullptr)
    {
        double newvalue = (value - 50) / 50.0 ; // -1.0 ~ 1.0
        tts->setPitch(newvalue);
    }
}
