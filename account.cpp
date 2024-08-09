#include <iostream>
#include <iomanip>
#include "account.h"
using namespace std;

Account::Account() {}

Account::Account(const LL& id, const LL& balance, const QString& pw)
{
    this->id = id;				// 생성시 입력
    this->balance = balance;
    this->pw = pw;
}

Account::~Account() {}

bool Account::addBalance(const LL& input)	// 잔액 +, 성공여부 반환
{
	balance = balance + input;
	return true;
}

bool Account::subBalance(const LL& output)	// 잔액 -, 성공여부 반환
{
	if (balance >= output) {			// 잔액이 출금액 이상일때
		balance = balance - output;	
		return true;					// true 반환
	}

	else {							// 잔액이 출금액 보다 작은 경우
		return false;				// false 반환
	}
}

void Account::printAccountInfo()	// 계좌번호, 잔액 출력
{
    // cout << endl;
    // cout << "계좌번호 : " << setfill('0') << setw(14) << this->id << setfill(' ') << endl;
    // cout << "잔액 : " << this->balance << endl;
}

bool Account::checkIdPw(const LL& id, const QString& pw)	//계좌 id,pw 일치여부 체크
{
	if ((this->id == id) && (this->pw == pw))
		return true;
	else
		return false;
}

