#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#define LL long long
#include <QString>
using namespace std;

class Account {
private:
    LL id = 0;			// ���¹�ȣ
    LL balance = 0;		// �ܾ�
    QString pw = "";		// ���� ��й�ȣ

public:
	Account();
    Account(const LL& id, const LL& balance, const QString& pw);	// ������ �Է�
	~Account();
	bool addBalance(const LL& input);		// �ܾ� +, �������� ��ȯ
	bool subBalance(const LL& output);		// �ܾ� -, �������� ��ȯ
	void printAccountInfo();		// ���¹�ȣ, �ܾ� ���
    bool checkIdPw(const LL& id, const QString& pw);	//���� id,pw ��ġ���� üũ

	// get �Լ�
	LL getId() const { return id; }
	LL getBalance() const { return balance; }
    QString getPw() const { return pw; }

	// set �Լ�
	void setId(const LL& id) { this->id = id; }
	void setBalance(const LL& balance) { this->balance = balance; }
    void setPw(const QString& pw) { this->pw = pw; }
};
#endif
