#ifndef _BANK_H_
#define _BANK_H_

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
#endif // BANK__H
