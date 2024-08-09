#ifndef BANK_H
#define BANK_H
#include <QMap>
#include <QString>
#include <QVector>
#include "user.h"
using namespace std;

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

    /* 변수 모음 */
    // bool useService = true;
    QMap<QString, int> idToIdx;
    QMap<long long, Account*> idToAccPtr;
    QVector<User> users;
    int curUserIdx = 0;

    /* 함수 모음 */
    void signUp(); // 회원가입
    void signIn();	// 로그인
    void loginSystem(); // 로그인 시스템
    bool checkCurUser(const QString& id, const QString& pw); // 현재 유저 확인
    void linkButtons();

public slots:
    void btnCheckAccount();
    void btnDeposit();
    void btnDepositAccountList();
    void btnMakeAccount();

    void btnWithdraw();
    void btnWithdrawAccountList();

    void btnTransfer();
    void btnTransferAccountList();


};
#endif // BANK_H
