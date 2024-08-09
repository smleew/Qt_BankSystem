#ifndef _BANK1_H_
#define _BANK1_H_
#include <map>
#include <string>
#include <vector>
#include "user.h"
using namespace std;

class Bank {
private:
    /* 변수 모음 */
    // bool useService = true;
    map<string, int> idToIdx;
    map<long long, Account*> idToAccPtr;
    vector<User> users;
    int curUserIdx = 0;

    /* 함수 모음 */
    void checkAccount();	//계좌 조회
    void makeAccount(); // 계좌 개설
    void signUp(); // 회원가입
    void signIn();	// 로그인
    void loginSystem(); // 로그인 시스템
    void deposit();		//입금
    void withdraw();	//출금
    void sendMoney(); // 송금
    bool checkCurUser(const string& id, const string& pw); // 현재 유저 확인
public:
    Bank();
    ~Bank();
    void bankService();		//은행업무
};
#endif
