#include "user.h"
using namespace std;

User::User()
{
}

User::User(const QString& id, const QString& pw)
{
	this->id = id;					// ������ �Է�
	this->pw = pw;
}

User::~User()
{
}

bool User::checkId(const QString& input)	// id ��ġ���� Ȯ��
{
	if (input == id)
		return true;
	else
		return false;
}

bool User::checkPw(const QString& input)	// pw ��ġ���� Ȯ��
{
	if (input == pw)
		return true;
	else
		return false;
}

void User::addAccount(const LL& id, const LL& balance, const QString& pw)
{								//���� ������ ���������� �迭�� �߰�
    Account newAccount(id, balance, pw);
    accounts.push_back(newAccount);
	accounts.push_back(Account(id, balance, pw));
}


