#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#define LL long long
#include <QString>
using namespace std;

class Account {
private:
    LL id = 0;			// 계좌번호
    LL balance = 0;		// 잔액
    QString pw = "";		// 계좌 비밀번호

public:
	Account();
    Account(const LL& id, const LL& balance, const QString& pw);	// 생성시 입력
	~Account();
	bool addBalance(const LL& input);		// 잔액 +, 성공여부 반환
	bool subBalance(const LL& output);		// 잔액 -, 성공여부 반환
	void printAccountInfo();		// 계좌번호, 잔액 출력
    bool checkIdPw(const LL& id, const QString& pw);	//계좌 id,pw 일치여부 체크

	// get 함수
	LL getId() const { return id; }
	LL getBalance() const { return balance; }
    QString getPw() const { return pw; }

	// set 함수
	void setId(const LL& id) { this->id = id; }
	void setBalance(const LL& balance) { this->balance = balance; }
    void setPw(const QString& pw) { this->pw = pw; }
};
#endif
