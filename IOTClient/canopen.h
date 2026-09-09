#ifndef CANOPEN_H
#define CANOPEN_H

#include <QWidget>

namespace Ui {
class CANOpen;
}

class CANOpen : public QWidget
{
    Q_OBJECT

public:
    explicit CANOpen(QWidget *parent = nullptr);
    ~CANOpen();

private:
    Ui::CANOpen *ui;
};

#endif // CANOPEN_H
