#include "canopen.h"
#include "ui_canopen.h"

CANOpen::CANOpen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CANOpen)
{
    ui->setupUi(this);
}

CANOpen::~CANOpen()
{
    delete ui;
}
