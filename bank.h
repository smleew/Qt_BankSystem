#ifndef BANK_H
#define BANK_H
#include <map>
#include <string>
#include <vector>
#include "user.h"
using namespace std;

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Bank;
}
QT_END_NAMESPACE

class Bank : public QWidget
{
    Q_OBJECT

public:
    Bank(QWidget *parent = nullptr);
    ~Bank();


private:
    Ui::Bank *ui;

    /* ���� ���� */
    // bool useService = true;
    map<string, int> idToIdx;
    map<long long, Account*> idToAccPtr;
    vector<User> users;
    int curUserIdx = 0;

    /* �Լ� ���� */
    void bankService();		//�������
    void checkAccount();	//���� ��ȸ
    void makeAccount(); // ���� ����
    void signUp(); // ȸ������
    void signIn();	// �α���
    void loginSystem(); // �α��� �ý���
    void deposit();		//�Ա�
    void withdraw();	//���
    void sendMoney(); // �۱�
    bool checkCurUser(const string& id, const string& pw); // ���� ���� Ȯ��

};
#endif // BANK_H
