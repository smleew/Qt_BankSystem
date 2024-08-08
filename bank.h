#ifndef BANK_H
#define BANK_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Bank;
}
QT_END_NAMESPACE

class Bank : public QWidget
{
    Q_OBJECT

public:
    Bank(QWidget *parent = nullptr);
    ~Bank();

private:
    Ui::Bank *ui;
};
#endif // BANK_H
