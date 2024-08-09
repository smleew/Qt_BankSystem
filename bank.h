#ifndef BANK_H
#define BANK_H
#include <map>
#include <string>
#include <vector>
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
    map<string, int> idToIdx;
    map<long long, Account*> idToAccPtr;
    vector<User> users;
    int curUserIdx = 0;

    /* 함수 모음 */
    void bankService();		//은행업무
    void checkAccount();	//계좌 조회
    void makeAccount(); // 계좌 개설
    void signUp(); // 회원가입
    void signIn();	// 로그인
    void loginSystem(); // 로그인 시스템
    void deposit();		//입금
    void withdraw();	//출금
    void sendMoney(); // 송금
    bool checkCurUser(const string& id, const string& pw); // 현재 유저 확인

};
#endif // BANK_H
