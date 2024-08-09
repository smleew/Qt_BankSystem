#ifndef _USER_H_
#define _USER_H_
#include <QString>
#include <QVector>
#include "account.h"
using namespace std;

class User {
private:
    QString id;			// ����� id
    QString pw;			// ����� pw
    QVector<Account> accounts;	// ���� �迭
public:
	User();
    User(const QString& id, const QString& pw);		// ������ �Է�
	~User();
    bool checkId(const QString& input);		// id ��ġ���� Ȯ��
    bool checkPw(const QString& input);		// pw ��ġ���� Ȯ��
    void addAccount(const LL& id, const LL& balance, const QString& pw); //���� ������ ���������� �迭�� �߰�
	

	// get �Լ�
    QString getId() const { return id; }
    QString getPw() const { return pw; }
    QVector<Account>& getAccounts() { return accounts; }; //���� �迭 ��ȯ, �ܺο��� �����ϵ���

	// set �Լ�
    void setId(QString id) { this->id = id; }
    void setPw(QString pw) { this->pw = pw; }
};

#endif
