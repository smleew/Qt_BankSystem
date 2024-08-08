#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#define LL long long
#include <string>
using namespace std;

class Account {
private:
	LL id;			// ���¹�ȣ
	LL balance;		// �ܾ�
	string pw;		// ���� ��й�ȣ

public:
	Account();
	Account(const LL& id, const LL& balance, const string& pw);	// ������ �Է�
	~Account();
	bool addBalance(const LL& input);		// �ܾ� +, �������� ��ȯ
	bool subBalance(const LL& output);		// �ܾ� -, �������� ��ȯ
	void printAccountInfo();		// ���¹�ȣ, �ܾ� ���
	bool checkIdPw(const LL& id, const string& pw);	//���� id,pw ��ġ���� üũ

	// get �Լ�
	LL getId() const { return id; }
	LL getBalance() const { return balance; }
	string getPw() const { return pw; }

	// set �Լ�
	void setId(const LL& id) { this->id = id; }
	void setBalance(const LL& balance) { this->balance = balance; }
	void setPw(const string& pw) { this->pw = pw; }
};
#endif