#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtTextToSpeech/QTextToSpeech>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_comboBox_engine_activated(int index);

    void on_comboBox_language_activated(int index);

    void on_comboBox_name_activated(int index);

    void on_horizontalSlider_rate_valueChanged(int value);

    void on_horizontalSlider_volume_valueChanged(int value);

    void on_horizontalSlider_pitch_valueChanged(int value);

    void on_pushButton_paly_clicked();

    void on_pushButton_resume_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_pause_clicked();

private:
    Ui::Widget *ui;
    QTextToSpeech *tts;
};
#endif // WIDGET_H
