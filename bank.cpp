#include "bank.h"
#include "./ui_bank.h"

Bank::Bank(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bank)
{
    ui->setupUi(this);
}

Bank::~Bank()
{
    delete ui;
}
