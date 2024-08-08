#ifndef _USER_H_
#define _USER_H_
#include <string>
#include "account.h"
#include <vector>
using namespace std;

class User {
private:
	string id;			// ����� id
	string pw;			// ����� pw
	vector<Account> accounts;	// ���� �迭
public:
	User();
	User(const string& id, const string& pw);		// ������ �Է�
	~User();
	bool checkId(const string& input);		// id ��ġ���� Ȯ��
	bool checkPw(const string& input);		// pw ��ġ���� Ȯ��
	void addAccount(const LL& id, const LL& balance, const string& pw); //���� ������ ���������� �迭�� �߰�
	

	// get �Լ�
	string getId() const { return id; }
	string getPw() const { return pw; }
	vector<Account>& getAccounts() { return accounts; }; //���� �迭 ��ȯ, �ܺο��� �����ϵ���

	// set �Լ�
	void setId(string id) { this->id = id; }
	void setPw(string pw) { this->pw = pw; }
};

#endif