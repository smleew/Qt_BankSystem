#include <iostream>
#include "user.h"
using namespace std;

User::User()
{
}

User::User(const string& id, const string& pw)
{
    this->id = id;					// 생성시 입력
    this->pw = pw;
}

User::~User()
{
}

bool User::checkId(const string& input)	// id 일치여부 확인
{
    if (input == id)
        return true;
    else
        return false;
}

bool User::checkPw(const string& input)	// pw 일치여부 확인
{
    if (input == pw)
        return true;
    else
        return false;
}

void User::addAccount(const LL& id, const LL& balance, const string& pw)
{								//계좌 생성후 계좌정보를 배열에 추가
    //Account newAccount(id, balance, pw);
    //accounts.push_back(newAccount);
    accounts.push_back(Account(id, balance, pw));

}


