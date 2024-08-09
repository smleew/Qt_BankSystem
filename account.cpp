#include <iostream>
#include <iomanip>
#include "account.h"
using namespace std;

Account::Account() {}

Account::Account(const LL& id, const LL& balance, const QString& pw)
{
    this->id = id;				// ������ �Է�
    this->balance = balance;
    this->pw = pw;
}

Account::~Account() {}

bool Account::addBalance(const LL& input)	// �ܾ� +, �������� ��ȯ
{
	balance = balance + input;
	return true;
}

bool Account::subBalance(const LL& output)	// �ܾ� -, �������� ��ȯ
{
	if (balance >= output) {			// �ܾ��� ��ݾ� �̻��϶�
		balance = balance - output;	
		return true;					// true ��ȯ
	}

	else {							// �ܾ��� ��ݾ� ���� ���� ���
		return false;				// false ��ȯ
	}
}

void Account::printAccountInfo()	// ���¹�ȣ, �ܾ� ���
{
    // cout << endl;
    // cout << "���¹�ȣ : " << setfill('0') << setw(14) << this->id << setfill(' ') << endl;
    // cout << "�ܾ� : " << this->balance << endl;
}

bool Account::checkIdPw(const LL& id, const QString& pw)	//���� id,pw ��ġ���� üũ
{
	if ((this->id == id) && (this->pw == pw))
		return true;
	else
		return false;
}

