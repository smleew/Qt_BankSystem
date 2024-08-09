#include "user.h"
using namespace std;

User::User()
{
}

User::User(const QString& id, const QString& pw)
{
	this->id = id;					// 생성시 입력
	this->pw = pw;
}

User::~User()
{
}

bool User::checkId(const QString& input)	// id 일치여부 확인
{
	if (input == id)
		return true;
	else
		return false;
}

bool User::checkPw(const QString& input)	// pw 일치여부 확인
{
	if (input == pw)
		return true;
	else
		return false;
}

void User::addAccount(const LL& id, const LL& balance, const QString& pw)
{								//계좌 생성후 계좌정보를 배열에 추가
    Account newAccount(id, balance, pw);
    accounts.push_back(newAccount);
	accounts.push_back(Account(id, balance, pw));
}


