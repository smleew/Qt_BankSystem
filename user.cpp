#include <iostream>
#include "user.h"
using namespace std;

User::User()
{
}

User::User(const string& id, const string& pw)
{
    this->id = id;					// ������ �Է�
    this->pw = pw;
}

User::~User()
{
}

bool User::checkId(const string& input)	// id ��ġ���� Ȯ��
{
    if (input == id)
        return true;
    else
        return false;
}

bool User::checkPw(const string& input)	// pw ��ġ���� Ȯ��
{
    if (input == pw)
        return true;
    else
        return false;
}

void User::addAccount(const LL& id, const LL& balance, const string& pw)
{								//���� ������ ���������� �迭�� �߰�
    //Account newAccount(id, balance, pw);
    //accounts.push_back(newAccount);
    accounts.push_back(Account(id, balance, pw));

}


