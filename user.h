#ifndef _USER_H_
#define _USER_H_
#include <QString>
#include <QVector>
#include "account.h"
using namespace std;

class User {
private:
    QString id;			// 사용자 id
    QString pw;			// 사용자 pw
    QVector<Account> accounts;	// 계좌 배열
public:
	User();
    User(const QString& id, const QString& pw);		// 생성시 입력
	~User();
    bool checkId(const QString& input);		// id 일치여부 확인
    bool checkPw(const QString& input);		// pw 일치여부 확인
    void addAccount(const LL& id, const LL& balance, const QString& pw); //계좌 생성후 계좌정보를 배열에 추가
	

	// get 함수
    QString getId() const { return id; }
    QString getPw() const { return pw; }
    QVector<Account>& getAccounts() { return accounts; }; //계좌 배열 반환, 외부에서 수정하도록

	// set 함수
    void setId(QString id) { this->id = id; }
    void setPw(QString pw) { this->pw = pw; }
};

#endif
