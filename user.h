#ifndef _USER_H_
#define _USER_H_
#include <string>
#include "account.h"
#include <vector>
using namespace std;

class User {
private:
	string id;			// 사용자 id
	string pw;			// 사용자 pw
	vector<Account> accounts;	// 계좌 배열
public:
	User();
	User(const string& id, const string& pw);		// 생성시 입력
	~User();
	bool checkId(const string& input);		// id 일치여부 확인
	bool checkPw(const string& input);		// pw 일치여부 확인
	void addAccount(const LL& id, const LL& balance, const string& pw); //계좌 생성후 계좌정보를 배열에 추가
	

	// get 함수
	string getId() const { return id; }
	string getPw() const { return pw; }
	vector<Account>& getAccounts() { return accounts; }; //계좌 배열 반환, 외부에서 수정하도록

	// set 함수
	void setId(string id) { this->id = id; }
	void setPw(string pw) { this->pw = pw; }
};

#endif